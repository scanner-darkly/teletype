#ifndef _TELETYPE_IO_H_
#define _TELETYPE_IO_H_

#include <stdbool.h>
#include <stdint.h>

// These functions are for interacting with the teletype hardware, each target
// must provide it's own implementation

// called when M or M.ACT are updated
extern void tele_metro_updated(void);

// called by M.RESET
extern void tele_metro_reset(void);

extern void tele_tr(uint8_t i, int16_t v);
extern void tele_cv(uint8_t i, int16_t v, uint8_t s);
extern void tele_cv_slew(uint8_t i, int16_t v);

extern void tele_update_in(void);

// inform target if there are delays
extern void tele_has_delays(bool has_delays);

// inform target if the stack has entries
extern void tele_has_stack(bool has_stack);

extern void tele_cv_off(uint8_t i, int16_t v);
extern void tele_ii_tx(uint8_t addr, uint8_t *data, uint8_t l);
extern void tele_ii_rx(uint8_t addr, uint8_t *data, uint8_t l);
extern void tele_scene(uint8_t i);

// called when a pattern is updated
extern void tele_pattern_updated(void);

extern void tele_kill(void);
extern void tele_mute(void);
extern bool tele_get_input_state(uint8_t);

// emulate grid key press
extern void grid_key_press(uint8_t x, int8_t y, int8_t z);

#endif
