#include "flash.h"

#include <string.h>

// asf
#include "flashc.h"
#include "print_funcs.h"

// this
#include "teletype.h"

#define FIRSTRUN_KEY 0x22

typedef struct {
    uint8_t button_states[GRID_BUTTON_COUNT >> 3];
    uint8_t fader_states[GRID_FADER_COUNT >> 1];
} grid_data_t;
static grid_data_t grid_data;

// NVRAM data structure located in the flash array.
typedef const struct {
    scene_script_t scripts[SCRIPT_COUNT];
    scene_pattern_t patterns[PATTERN_COUNT];
    grid_data_t grid_data;
    char text[SCENE_TEXT_LINES][SCENE_TEXT_CHARS];
} nvram_scene_t;

typedef const struct {
    nvram_scene_t scenes[SCENE_SLOTS];
    uint8_t last_scene;
    uint8_t fresh;
} nvram_data_t;

static __attribute__((__section__(".flash_nvram"))) nvram_data_t f;

static void pack_grid(scene_state_t *scene);
static void unpack_grid(scene_state_t *scene);

void flash_prepare() {
    // if it's not empty return
    if (f.fresh == FIRSTRUN_KEY) return;

    print_dbg("\r\n:::: first run, clearing flash");
    print_dbg("\r\nflash size: ");
    print_dbg_ulong(sizeof(f));

    // blank scene to write to flash
    scene_state_t scene;
    ss_init(&scene);

    char text[SCENE_TEXT_LINES][SCENE_TEXT_CHARS];
    memset(text, 0, SCENE_TEXT_LINES * SCENE_TEXT_CHARS);

    for (uint8_t i = 0; i < SCENE_SLOTS; i++) { flash_write(i, &scene, &text); }
    flash_update_last_saved_scene(0);
    flashc_memset8((void *)&f.fresh, FIRSTRUN_KEY, 1, true);
}

void flash_write(uint8_t preset_no, scene_state_t *scene,
                 char (*text)[SCENE_TEXT_LINES][SCENE_TEXT_CHARS]) {
    flashc_memcpy((void *)&f.scenes[preset_no].scripts, ss_scripts_ptr(scene),
                  ss_scripts_size(), true);
    flashc_memcpy((void *)&f.scenes[preset_no].patterns, ss_patterns_ptr(scene),
                  ss_patterns_size(), true);
    pack_grid(scene);
    flashc_memcpy((void *)&f.scenes[preset_no].grid_data, &grid_data,
                  sizeof(grid_data_t), true);
    flashc_memcpy((void *)&f.scenes[preset_no].text, text,
                  SCENE_TEXT_LINES * SCENE_TEXT_CHARS, true);
}

void flash_read(uint8_t preset_no, scene_state_t *scene,
                char (*text)[SCENE_TEXT_LINES][SCENE_TEXT_CHARS]) {
    memcpy(ss_scripts_ptr(scene), &f.scenes[preset_no].scripts,
           ss_scripts_size());
    memcpy(ss_patterns_ptr(scene), &f.scenes[preset_no].patterns,
           ss_patterns_size());
    memcpy(&grid_data, &f.scenes[preset_no].grid_data, sizeof(grid_data_t));
    unpack_grid(scene);           
    memcpy(text, &f.scenes[preset_no].text,
           SCENE_TEXT_LINES * SCENE_TEXT_CHARS);
}

uint8_t flash_last_saved_scene() {
    return f.last_scene;
}

void flash_update_last_saved_scene(uint8_t preset_no) {
    flashc_memset8((void *)&f.last_scene, preset_no, 1, true);
}

const char *flash_scene_text(uint8_t preset_no, size_t line) {
    return f.scenes[preset_no].text[line];
}

static void pack_grid(scene_state_t *scene) {
    uint8_t byte = 0;
    uint8_t byte_count = 0;
    for (uint16_t i = 0; i < GRID_BUTTON_COUNT; i++) {
        byte |= (scene->grid.button[i].state != 0) << (i & 7);
        if ((i & 7) == 7) {
            grid_data.button_states[byte_count++] = byte;
            byte = 0;
        }
    }
    for (uint16_t i = 0; i < GRID_FADER_COUNT; i += 2) {
        grid_data.fader_states[i >> 1] = (scene->grid.fader[i].value << 4) + 
            scene->grid.fader[i+1].value;
    }
}

static void unpack_grid(scene_state_t *scene) {
    for (uint16_t i = 0; i < GRID_BUTTON_COUNT; i++) {
        scene->grid.button[i].state = 
            0 != (grid_data.button_states[i >> 3] & (1 << (i & 7)));
    }
    for (uint16_t i = 0; i < GRID_FADER_COUNT; i += 2) {
        scene->grid.fader[i].value = grid_data.fader_states[i >> 1] >> 4;
        scene->grid.fader[i+1].value = grid_data.fader_states[i >> 1] & 0b1111;
    }
} 