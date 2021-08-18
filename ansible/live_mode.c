#include "live_mode.h"

// teletype
#include "teletype_io.h"

#define MAX_DASH_VARS 16

static uint8_t sub_mode;

uint8_t grid_page = 0;
uint8_t grid_show_controls = 0;

static int16_t dash_values[MAX_DASH_VARS];

// teletype_io.h
void tele_has_delays(bool has_delays) {}
void tele_has_stack(bool has_stack) {}
void tele_mute() {}

void set_live_submode(u8 submode) {
    sub_mode = submode;
}

void select_dash_screen(uint8_t screen) {
    if (sub_mode != SUB_MODE_DASH) {
        sub_mode = SUB_MODE_DASH;
    }
}

void print_dashboard_value(uint8_t index, int16_t value) {
    if (index >= MAX_DASH_VARS) return;
    if (dash_values[index] != value) {
        dash_values[index] = value;
    }
}

int16_t get_dashboard_value(uint8_t index) {
    if (index >= MAX_DASH_VARS) return 0;
    return dash_values[index];
}

void set_slew_icon(bool display) {}
void set_metro_icon(bool display) {}

void set_vars_updated(void) {}
void set_dash_updated() {}
void set_grid_updated(void) {}
void set_mutes_updated() {}

void init_live_mode(void) {
    sub_mode = SUB_MODE_OFF;
}

void set_live_mode(void) {
    if (sub_mode == SUB_MODE_FULLGRID) sub_mode = SUB_MODE_GRID;
}

uint8_t get_live_sub_mode() {
    return sub_mode;
}

void history_next(void) {}
void history_prev(void) {}
void execute_line(void) {}
void process_live_keys(uint8_t key, uint8_t mod_key, bool is_held_key,
                       bool is_release, scene_state_t *ss) {}

uint8_t screen_refresh_live() {
  return 0;
}
