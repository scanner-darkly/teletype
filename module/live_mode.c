#include "live_mode.h"

#include <string.h>

// this
#include "flash.h"
#include "gitversion.h"
#include "globals.h"
#include "keyboard_helper.h"
#include "line_editor.h"

// teletype
#include "teletype_io.h"

// libavr32
#include "font.h"
#include "region.h"
#include "util.h"

// asf
#include "conf_usb_host.h"  // needed in order to include "usb_protocol_hid.h"
#include "usb_protocol_hid.h"

#define MAX_HISTORY_SIZE 16
static tele_command_t history[MAX_HISTORY_SIZE];  // newest entry in index 0
static int8_t history_line;                       // -1 for not selected
static int8_t history_top;                        // -1 when empty

static line_editor_t le;
static process_result_t output;
static error_t status;
static char error_msg[TELE_ERROR_MSG_LENGTH];
static bool show_welcome_message;
static screen_grid_mode grid_mode = GRID_MODE_OFF;
static uint8_t grid_page = 0, grid_view_changed = 0;
static uint8_t grid_x1 = 0, grid_y1 = 0, grid_x2 = 0, grid_y2 = 0;

static const uint8_t D_INPUT = 1 << 0;
static const uint8_t D_LIST = 1 << 1;
static const uint8_t D_MESSAGE = 1 << 2;
static const uint8_t D_ALL = 0xFF;
static uint8_t dirty;

static const uint8_t A_METRO = 1 << 0;
static const uint8_t A_SLEW = 1 << 1;
static const uint8_t A_DELAY = 1 << 2;
static const uint8_t A_STACK = 1 << 3;
static const uint8_t A_MUTES = 1 << 4;
static uint8_t activity_prev;
static uint8_t activity;

// teletype_io.h
void tele_has_delays(bool has_delays) {
    if (has_delays)
        activity |= A_DELAY;
    else
        activity &= ~A_DELAY;
}

void tele_has_stack(bool has_stack) {
    if (has_stack)
        activity |= A_STACK;
    else
        activity &= ~A_STACK;
}

void tele_mute() {
    activity |= A_MUTES;
}

// set icons
void set_slew_icon(bool display) {
    if (display)
        activity |= A_SLEW;
    else
        activity &= ~A_SLEW;
}

void set_metro_icon(bool display) {
    if (display)
        activity |= A_METRO;
    else
        activity &= ~A_METRO;
}

// main mode functions
void init_live_mode() {
    status = E_OK;
    show_welcome_message = true;
    dirty = D_ALL;
    activity_prev = 0xFF;
    history_top = -1;
    history_line = -1;
}

void set_live_mode() {
    line_editor_set(&le, "");
    history_line = -1;
    dirty = D_ALL;
    activity_prev = 0xFF;
    grid_view_changed = true;
    if (grid_mode == GRID_MODE_FULL)
        grid_mode = GRID_MODE_LED;
}

void process_live_keys(uint8_t k, uint8_t m, bool is_held_key, bool is_release, scene_state_t *ss) {
    if (is_release) {
        if (match_ctrl(m, k, HID_SPACEBAR) || 
            (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_SPACEBAR))) {
            grid_process_key(ss, grid_x1, grid_y1, 0);
        }
        return;
    }
    
    // <down> or C-n: history next
    if ((match_no_mod(m, k, HID_DOWN) || match_ctrl(m, k, HID_N))
        && grid_mode != GRID_MODE_FULL) {
        if (history_line > 0) {
            history_line--;
            line_editor_set_command(&le, &history[history_line]);
        }
        else {
            history_line = -1;
            line_editor_set(&le, "");
        }
        dirty |= D_INPUT;
    }
    // <up> or C-p: history previous
    else if ((match_no_mod(m, k, HID_UP) || match_ctrl(m, k, HID_P))
        && grid_mode != GRID_MODE_FULL) {
        if (history_line < history_top) {
            history_line++;
            line_editor_set_command(&le, &history[history_line]);
            dirty |= D_INPUT;
        }
    }
    // C-G: toggle grid view
    else if (match_ctrl(m, k, HID_G) || 
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_G))) {
        if (++grid_mode == GRID_MODE_LAST) {
            grid_mode = GRID_MODE_OFF;
            set_live_mode();
        } else grid_view_changed = true;
    }
    // C-<up>: move grid cursor
    else if (match_ctrl(m, k, HID_UP) ||
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_UP))) {
        grid_y1 = (grid_y1 + GRID_MAX_DIMENSION - 1) % GRID_MAX_DIMENSION;
        grid_x2 = grid_x1;
        grid_y2 = grid_y1;
        grid_view_changed = true;
    }
    // C-<down>: move grid cursor
    else if (match_ctrl(m, k, HID_DOWN) ||
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_DOWN))) {
        grid_y1 = (grid_y1 + 1) % GRID_MAX_DIMENSION;
        grid_x2 = grid_x1;
        grid_y2 = grid_y1;
        grid_view_changed = true;
    }
    // C-<left>: move grid cursor
    else if (match_ctrl(m, k, HID_LEFT) ||
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_LEFT))) {
        grid_x1 = (grid_x1 + GRID_MAX_DIMENSION - 1) % GRID_MAX_DIMENSION;
        grid_x2 = grid_x1;
        grid_y2 = grid_y1;
        grid_view_changed = true;
    }
    // C-<right>: move grid cursor
    else if (match_ctrl(m, k, HID_RIGHT) ||
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_RIGHT))) {
        grid_x1 = (grid_x1 + 1) % GRID_MAX_DIMENSION;
        grid_x2 = grid_x1;
        grid_y2 = grid_y1;
        grid_view_changed = true;
    }
    // C-S-<up>: expand grid area up
    else if (match_shift_ctrl(m, k, HID_UP) ||
        (grid_mode == GRID_MODE_FULL && match_shift(m, k, HID_UP))) {
        if (grid_y2 > 0) {
            grid_y2--;
            grid_view_changed = true;
        }
    }
    // C-S-<down>: expand grid area down
    else if (match_shift_ctrl(m, k, HID_DOWN) ||
        (grid_mode == GRID_MODE_FULL && match_shift(m, k, HID_DOWN))) {
        if (grid_y2 < GRID_MAX_DIMENSION - 1) {
            grid_y2++;
            grid_view_changed = true;
        }
    }
    // C-S-<left>: expand grid area left
    else if (match_shift_ctrl(m, k, HID_LEFT) ||
        (grid_mode == GRID_MODE_FULL && match_shift(m, k, HID_LEFT))) {
        if (grid_x2 > 0) {
            grid_x2--;
            grid_view_changed = true;
        }
    }
    // C-S-<right>: expand grid area right
    else if (match_shift_ctrl(m, k, HID_RIGHT) ||
        (grid_mode == GRID_MODE_FULL && match_shift(m, k, HID_RIGHT))) {
        if (grid_x2 < GRID_MAX_DIMENSION - 1) {
            grid_x2++;
            grid_view_changed = true;
        }
    }
    // C-<space>: emulate grid press
    else if (!is_held_key && (match_ctrl(m, k, HID_SPACEBAR) ||
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_SPACEBAR)))) {
        grid_x2 = grid_x1;
        grid_y2 = grid_y1;
        grid_view_changed = true;
        grid_process_key(ss, grid_x1, grid_y1, 1);
    }
    // C-<PrtSc>: insert coordinates / size
    else if (!is_held_key && match_ctrl(m, k, HID_PRINTSCREEN) &&
        grid_mode != GRID_MODE_FULL) {
        u8 area_x, area_y, area_w, area_h;
        if (grid_x1 < grid_x2) {
            area_x = grid_x1;
            area_w = grid_x2 + 1 - grid_x1;
        } else {
            area_x = grid_x2;
            area_w = grid_x1 + 1 - grid_x2;
        }
        if (grid_y1 < grid_y2) {
            area_y = grid_y1;
            area_h = grid_y2 + 1 - grid_y1;
        } else {
            area_y = grid_y2;
            area_h = grid_y1 + 1 - grid_y2;
        }
        if (area_x > 9) {
            line_editor_process_keys(&le, HID_1, HID_MODIFIER_NONE, false);
            area_x -= 10;
        }
        line_editor_process_keys(&le, 
            area_x ? HID_1 + area_x - 1 : HID_0, HID_MODIFIER_NONE, false);
        line_editor_process_keys(&le, HID_SPACEBAR, HID_MODIFIER_NONE, false);
        if (area_y > 9) {
            line_editor_process_keys(&le, HID_1, HID_MODIFIER_NONE, false);
            area_y -= 10;
        }
        line_editor_process_keys(&le, 
            area_y ? HID_1 + area_y - 1 : HID_0, HID_MODIFIER_NONE, false);
        line_editor_process_keys(&le, HID_SPACEBAR, HID_MODIFIER_NONE, false);
        if (area_w > 9) {
            line_editor_process_keys(&le, HID_1, HID_MODIFIER_NONE, false);
            area_w -= 10;
        }
        line_editor_process_keys(&le, 
            area_w ? HID_1 + area_w - 1 : HID_0, HID_MODIFIER_NONE, false);
        line_editor_process_keys(&le, HID_SPACEBAR, HID_MODIFIER_NONE, false);
        if (area_h > 9) {
            line_editor_process_keys(&le, HID_1, HID_MODIFIER_NONE, false);
            area_h -= 10;
        }
        line_editor_process_keys(&le, 
            area_h ? HID_1 + area_h - 1 : HID_0, HID_MODIFIER_NONE, false);
        line_editor_process_keys(&le, HID_SPACEBAR, HID_MODIFIER_NONE, false);
        dirty |= D_INPUT;
    }
    // C-<tab>: toggle grid page
    else if (match_ctrl(m, k, HID_SLASH) ||
        (grid_mode == GRID_MODE_FULL && match_no_mod(m, k, HID_SLASH))) {
        if (++grid_page > 1) grid_page = 0;
        grid_view_changed = true;
    }
    // <enter>: execute command
    else if (match_no_mod(m, k, HID_ENTER) && grid_mode != GRID_MODE_FULL) {
        dirty |= D_MESSAGE;  // something will definitely happen
        dirty |= D_INPUT;

        tele_command_t command;

        status = parse(line_editor_get(&le), &command, error_msg);
        if (status != E_OK)
            return;  // quit, screen_refresh_live will display the error message

        status = validate(&command, error_msg);
        if (status != E_OK)
            return;  // quit, screen_refresh_live will display the error message

        if (command.length) {
            // increase history_size up to a maximum
            history_top++;
            if (history_top >= MAX_HISTORY_SIZE)
                history_top = MAX_HISTORY_SIZE - 1;

            // shuffle the history up
            // should really use some sort of ring buffer
            for (size_t i = history_top; i > 0; i--) {
                memcpy(&history[i], &history[i - 1], sizeof(command));
            }
            memcpy(&history[0], &command, sizeof(command));

            ss_clear_script(&scene_state, TEMP_SCRIPT);
            ss_overwrite_script_command(&scene_state, TEMP_SCRIPT, 0, &command);
            exec_state_t es;
            es_init(&es);
            es_push(&es);
            es_variables(&es)->script_number = TEMP_SCRIPT;

            output = run_script_with_exec_state(&scene_state, &es, TEMP_SCRIPT);
        }

        history_line = -1;
        line_editor_set(&le, "");
    }
    // [ or ]: switch to edit mode
    else if (match_no_mod(m, k, HID_OPEN_BRACKET) ||
             match_no_mod(m, k, HID_CLOSE_BRACKET)) {
        set_mode(M_EDIT);
    }
    // pass the key though to the line editor
    else if (grid_mode != GRID_MODE_FULL) {
        bool processed = line_editor_process_keys(&le, k, m, is_held_key);
        if (processed) dirty |= D_INPUT;
    }
    show_welcome_message = false;
}


bool screen_refresh_live(scene_state_t *ss) {
    bool screen_dirty = false;
    
    if (grid_mode != GRID_MODE_OFF && (grid_view_changed || ss->grid.scr_dirty)) {
        grid_view_changed = 0;
        screen_dirty = true;
        grid_screen_refresh(ss, grid_mode, grid_page, grid_x1, grid_y1, grid_x2, grid_y2);
    }
    if (grid_mode == GRID_MODE_FULL) return true;
    
    if (dirty & D_INPUT) {
        line_editor_draw(&le, '>', &line[7]);
        screen_dirty = true;
        dirty &= ~D_INPUT;
    }

    if (dirty & D_MESSAGE) {
        char s[32];
        if (status != E_OK) {
            strcpy(s, tele_error(status));
            if (error_msg[0]) {
                size_t len = strlen(s);
                strcat(s, ": ");
                strncat(s, error_msg, 32 - len - 3);
                error_msg[0] = 0;
            }
            status = E_OK;
        }
        else if (output.has_value) {
            itoa(output.value, s, 10);
            output.has_value = false;
        }
        else if (show_welcome_message) {
            strcpy(s, TELETYPE_VERSION ": ");
            strcat(s, git_version);
        }
        else {
            s[0] = 0;
        }

        region_fill(&line[6], 0);
        font_string_region_clip(&line[6], s, 0, 0, 0x4, 0);

        screen_dirty = true;
        dirty &= ~D_MESSAGE;
    }

    if (dirty & D_LIST && grid_mode == GRID_MODE_OFF) {
        for (int i = 0; i < 6; i++) region_fill(&line[i], 0);

        screen_dirty = true;
        dirty &= ~D_LIST;
    }

    if (activity != activity_prev && grid_mode == GRID_MODE_OFF) {
        region_fill(&line[0], 0);

        // slew icon
        uint8_t slew_fg = activity & A_SLEW ? 15 : 1;
        line[0].data[98 + 0 + 512] = slew_fg;
        line[0].data[98 + 1 + 384] = slew_fg;
        line[0].data[98 + 2 + 256] = slew_fg;
        line[0].data[98 + 3 + 128] = slew_fg;
        line[0].data[98 + 4 + 0] = slew_fg;
        
        // delay icon
        uint8_t delay_fg = activity & A_DELAY ? 15 : 1;
        line[0].data[106 + 0 + 0] = delay_fg;
        line[0].data[106 + 1 + 0] = delay_fg;
        line[0].data[106 + 2 + 0] = delay_fg;
        line[0].data[106 + 3 + 0] = delay_fg;
        line[0].data[106 + 4 + 0] = delay_fg;
        line[0].data[106 + 0 + 128] = delay_fg;
        line[0].data[106 + 0 + 256] = delay_fg;
        line[0].data[106 + 0 + 384] = delay_fg;
        line[0].data[106 + 0 + 512] = delay_fg;
        line[0].data[106 + 4 + 128] = delay_fg;
        line[0].data[106 + 4 + 256] = delay_fg;
        line[0].data[106 + 4 + 384] = delay_fg;
        line[0].data[106 + 4 + 512] = delay_fg;

        // queue icon
        uint8_t stack_fg = activity & A_STACK ? 15 : 1;
        line[0].data[114 + 0 + 0] = stack_fg;
        line[0].data[114 + 1 + 0] = stack_fg;
        line[0].data[114 + 2 + 0] = stack_fg;
        line[0].data[114 + 3 + 0] = stack_fg;
        line[0].data[114 + 4 + 0] = stack_fg;
        line[0].data[114 + 0 + 256] = stack_fg;
        line[0].data[114 + 1 + 256] = stack_fg;
        line[0].data[114 + 2 + 256] = stack_fg;
        line[0].data[114 + 3 + 256] = stack_fg;
        line[0].data[114 + 4 + 256] = stack_fg;
        line[0].data[114 + 0 + 512] = stack_fg;
        line[0].data[114 + 1 + 512] = stack_fg;
        line[0].data[114 + 2 + 512] = stack_fg;
        line[0].data[114 + 3 + 512] = stack_fg;
        line[0].data[114 + 4 + 512] = stack_fg;

        // metro icon
        uint8_t metro_fg = activity & A_METRO ? 15 : 1;
        line[0].data[122 + 0 + 0] = metro_fg;
        line[0].data[122 + 0 + 128] = metro_fg;
        line[0].data[122 + 0 + 256] = metro_fg;
        line[0].data[122 + 0 + 384] = metro_fg;
        line[0].data[122 + 0 + 512] = metro_fg;
        line[0].data[122 + 1 + 128] = metro_fg;
        line[0].data[122 + 2 + 256] = metro_fg;
        line[0].data[122 + 3 + 128] = metro_fg;
        line[0].data[122 + 4 + 0] = metro_fg;
        line[0].data[122 + 4 + 128] = metro_fg;
        line[0].data[122 + 4 + 256] = metro_fg;
        line[0].data[122 + 4 + 384] = metro_fg;
        line[0].data[122 + 4 + 512] = metro_fg;

        // mutes
        for (size_t i = 0; i < 8; i++) {
            // make it staggered to match how the device looks
            size_t stagger = i % 2 ? 384 : 128;
            uint8_t mute_fg = ss_get_mute(&scene_state, i) ? 15 : 1;
            line[0].data[87 + i + stagger] = mute_fg;
        }

        activity_prev = activity;
        screen_dirty = true;
        activity &= ~A_MUTES;
    }

    return screen_dirty;
}
