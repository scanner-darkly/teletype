#ifndef _GRID_H_
#define _GRID_H_

#include "monome.h"
#include "state.h"

#define SG ss->grid
#define GB ss->grid.button[i]
#define GBC ss->grid.button[i].common
#define GF ss->grid.fader[i]
#define GFC ss->grid.fader[i].common
#define GXY ss->grid.xypad[i]
#define GXYC ss->grid.xypad[i].common

typedef enum {
    GRID_MODE_OFF = 0,
    GRID_MODE_EDIT,
    GRID_MODE_FULL,
    GRID_MODE_LAST
} screen_grid_mode;

extern void grid_refresh(scene_state_t *ss);
extern void grid_screen_refresh(scene_state_t *ss, screen_grid_mode mode,
    u8 page, u8 ctrl, u8 x1, u8 y1, u8 x2, u8 y2);
extern void grid_process_key(scene_state_t *ss, u8 x, u8 y, u8 z,
    u8 ignore_rotate);
extern void grid_process_fader_slew(scene_state_t *ss);

#endif
