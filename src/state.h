#ifndef _STATE_H_
#define _STATE_H_

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "command.h"
#include "every.h"
#include "turtle.h"
#include "types.h"

#define STACK_SIZE 16
#define CV_COUNT 4
#define Q_LENGTH 64
#define TR_COUNT 4
#define TRIGGER_INPUTS 8
#define DELAY_SIZE 8
#define STACK_OP_SIZE 16
#define PATTERN_COUNT 4
#define PATTERN_LENGTH 64
#define SCRIPT_MAX_COMMANDS 6
#define SCRIPT_COUNT 11
#define EXEC_DEPTH 8
#define WHILE_DEPTH 10000

#define GRID_GROUP_COUNT 64
#define GRID_MAX_DIMENSION 16
#define GRID_BUTTON_COUNT 256
#define GRID_FADER_COUNT 64
#define GRID_XYPAD_COUNT 8
#define LED_DIM -1
#define LED_BRI -2
#define LED_OFF -3
// H - horizontal, V - vertical
// C - coarse, F - fine
// H must be even, V must be odd
#define FADER_CH_BAR 0
#define FADER_CV_BAR 1
#define FADER_CH_DOT 2
#define FADER_CV_DOT 3
#define FADER_COARSE FADER_CV_DOT
#define FADER_FH_BAR 4
#define FADER_FV_BAR 5
#define FADER_FH_DOT 6
#define FADER_FV_DOT 7

#define METRO_MIN_MS 25
#define METRO_MIN_UNSUPPORTED_MS 2

////////////////////////////////////////////////////////////////////////////////
// SCENE STATE /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    int16_t a;
    int16_t b;
    int16_t c;
    int16_t cv[CV_COUNT];
    int16_t cv_off[CV_COUNT];
    int16_t cv_slew[CV_COUNT];
    int16_t d;
    int16_t drunk;
    int16_t drunk_max;
    int16_t drunk_min;
    int16_t drunk_wrap;
    int16_t flip;
    int16_t in;
    int16_t m;
    bool m_act;
    bool mutes[TRIGGER_INPUTS];
    int16_t o;
    int16_t o_inc;
    int16_t o_min;
    int16_t o_max;
    int16_t o_wrap;
    int16_t p_n;
    int16_t param;
    int16_t q[Q_LENGTH];
    int16_t q_n;
    int16_t scene;
    int16_t t;
    int16_t time;
    int16_t time_act;
    int16_t tr[TR_COUNT];
    int16_t tr_pol[TR_COUNT];
    int16_t tr_time[TR_COUNT];
    int16_t x;
    int16_t y;
    int16_t z;
} scene_variables_t;

typedef struct {
    int16_t idx;
    uint16_t len;
    uint16_t wrap;
    int16_t start;
    int16_t end;
    int16_t val[PATTERN_LENGTH];
} scene_pattern_t;

typedef struct {
    // TODO add a delay variables struct?
    tele_command_t commands[DELAY_SIZE];
    int16_t time[DELAY_SIZE];
    uint8_t origin[DELAY_SIZE];
    uint8_t count;
} scene_delay_t;

typedef struct {
    tele_command_t commands[STACK_OP_SIZE];
    uint8_t top;
} scene_stack_op_t;

typedef struct {
    uint8_t l;
    tele_command_t c[SCRIPT_MAX_COMMANDS];
    bool comment[SCRIPT_MAX_COMMANDS];
    every_count_t every[SCRIPT_MAX_COMMANDS];
    int16_t last_time;
} scene_script_t;

 typedef struct {
    u8 enabled;
    u8 group;
    u8 x, y;
    u8 w, h;
    u8 level;
    s8 script;
} grid_common_t;

typedef struct {
    u8 enabled;
    s8 script;
    s16 fader_min;
    s16 fader_max;
} grid_group_t;

typedef struct {
    grid_common_t common;
    u8 latch;
    u8 state;
} grid_button_t;

typedef struct {
    grid_common_t common;
    u8 type;
    u8 value;
    u8 slide;
    u8 slide_acc;
    u8 slide_end;
    u8 slide_delta;
    u8 slide_dir;
} grid_fader_t;

typedef struct {
    grid_common_t common;
    u8 value_x;
    u8 value_y;
} grid_xypad_t;

typedef struct {
    u8 grid_dirty;
    u8 scr_dirty;
    
    u8 rotate;
    u8 dim;

    u8 current_group;
    u8 latest_group;
    u8 latest_button;
    u8 latest_fader;
    
    s8 leds[GRID_MAX_DIMENSION][GRID_MAX_DIMENSION];
    grid_group_t group[GRID_GROUP_COUNT];
    
    grid_button_t button[GRID_BUTTON_COUNT];
    grid_fader_t fader[GRID_FADER_COUNT];
    grid_xypad_t xypad[GRID_XYPAD_COUNT];
} scene_grid_t;

typedef struct {
    bool initializing;
    scene_variables_t variables;
    scene_pattern_t patterns[PATTERN_COUNT];
    scene_delay_t delay;
    scene_stack_op_t stack_op;
    int16_t tr_pulse_timer[TR_COUNT];
    scene_script_t scripts[SCRIPT_COUNT];
    scene_turtle_t turtle;
    bool every_last;
    scene_grid_t grid;
} scene_state_t;

extern void ss_init(scene_state_t *ss);
extern void ss_variables_init(scene_state_t *ss);
extern void ss_patterns_init(scene_state_t *ss);
extern void ss_pattern_init(scene_state_t *ss, size_t pattern_no);
extern void ss_grid_init(scene_state_t *ss);
extern void ss_grid_common_init(grid_common_t *gc);

extern void ss_set_in(scene_state_t *ss, int16_t value);
extern void ss_set_param(scene_state_t *ss, int16_t value);
extern void ss_set_scene(scene_state_t *ss, int16_t value);

extern bool ss_get_mute(scene_state_t *ss, size_t idx);
extern void ss_set_mute(scene_state_t *ss, size_t idx, bool value);

extern int16_t ss_get_pattern_idx(scene_state_t *ss, size_t pattern);
extern void ss_set_pattern_idx(scene_state_t *ss, size_t pattern, int16_t i);
extern int16_t ss_get_pattern_len(scene_state_t *ss, size_t pattern);
extern void ss_set_pattern_len(scene_state_t *ss, size_t pattern, int16_t l);
extern uint16_t ss_get_pattern_wrap(scene_state_t *ss, size_t pattern);
extern void ss_set_pattern_wrap(scene_state_t *ss, size_t pattern,
                                uint16_t wrap);
extern int16_t ss_get_pattern_start(scene_state_t *ss, size_t pattern);
extern void ss_set_pattern_start(scene_state_t *ss, size_t pattern,
                                 int16_t start);
extern int16_t ss_get_pattern_end(scene_state_t *ss, size_t pattern);
extern void ss_set_pattern_end(scene_state_t *ss, size_t pattern, int16_t end);
extern int16_t ss_get_pattern_val(scene_state_t *ss, size_t pattern,
                                  size_t idx);
extern void ss_set_pattern_val(scene_state_t *ss, size_t pattern, size_t idx,
                               int16_t val);
extern scene_pattern_t *ss_patterns_ptr(scene_state_t *ss);
extern size_t ss_patterns_size(void);

uint8_t ss_get_script_len(scene_state_t *ss, script_number_t idx);
const tele_command_t *ss_get_script_command(scene_state_t *ss,
                                            script_number_t script_idx,
                                            size_t c_idx);
bool ss_get_script_comment(scene_state_t *ss, script_number_t script_idx,
                           size_t c_idx);
void ss_toggle_script_comment(scene_state_t *ss, script_number_t script_idx,
                              size_t c_idx);
void ss_overwrite_script_command(scene_state_t *ss, script_number_t script_idx,
                                 size_t command_idx, const tele_command_t *cmd);
void ss_insert_script_command(scene_state_t *ss, script_number_t script_idx,
                              size_t command_idx, const tele_command_t *cmd);
void ss_delete_script_command(scene_state_t *ss, script_number_t script_idx,
                              size_t command_idx);
void ss_clear_script(scene_state_t *ss, size_t script_idx);

scene_script_t *ss_scripts_ptr(scene_state_t *ss);
size_t ss_scripts_size(void);
int16_t ss_get_script_last(scene_state_t *ss, script_number_t idx);
void ss_update_script_last(scene_state_t *ss, script_number_t idx);
every_count_t *ss_get_every(scene_state_t *ss, script_number_t idx,
                            uint8_t line);
void ss_sync_every(scene_state_t *ss, int16_t count);
bool every_is_now(scene_state_t *ss, every_count_t *e);
bool skip_is_now(scene_state_t *ss, every_count_t *e);
scene_turtle_t *ss_turtle_get(scene_state_t *);
void ss_turtle_set(scene_state_t *, scene_turtle_t *);
int16_t ss_turtle_get_val(scene_state_t *, scene_turtle_t *);
void ss_turtle_set_val(scene_state_t *, scene_turtle_t *, int16_t);

////////////////////////////////////////////////////////////////////////////////
// EXEC STATE //////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    bool if_else_condition;
    int16_t i;
    bool while_continue;
    uint16_t while_depth;
    bool breaking;
    script_number_t script_number;
    uint8_t line_number;
    bool delayed;
} exec_vars_t;

typedef struct {
    exec_vars_t variables[EXEC_DEPTH];
    uint8_t exec_depth;
    bool overflow;
} exec_state_t;

extern void es_init(exec_state_t *es);
extern size_t es_depth(exec_state_t *es);
extern size_t es_push(exec_state_t *es);
extern size_t es_pop(exec_state_t *es);
extern void es_set_script_number(exec_state_t *es, uint8_t script_number);
extern void es_set_line_number(exec_state_t *es, uint8_t line_number);
extern uint8_t es_get_line_number(exec_state_t *es);
extern exec_vars_t *es_variables(exec_state_t *es);

////////////////////////////////////////////////////////////////////////////////
// COMMAND STATE ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

typedef struct {
    int16_t values[STACK_SIZE];
    int16_t top;
} command_state_stack_t;

typedef struct {
    command_state_stack_t stack;
} command_state_t;

extern void cs_init(command_state_t *cs);
extern int16_t cs_stack_size(command_state_t *cs);

// by declaring the following static inline, each compilation unit (i.e. C
// file), gets its own copy of the function
static inline int16_t cs_pop(command_state_t *cs) {
    cs->stack.top--;
    return cs->stack.values[cs->stack.top];
}

static inline void cs_push(command_state_t *cs, int16_t data) {
    cs->stack.values[cs->stack.top] = data;
    cs->stack.top++;
}


#endif
