#include "ops/er301.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"
#include "telex.h"

static void op_SC_TR_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_SC_TR_TOG_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_SC_TR_PULSE_get(const void *data, scene_state_t *ss,
                               exec_state_t *es, command_state_t *cs);
static void op_SC_TR_TIME_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_SC_TR_POL_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);

static void op_SC_CV_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);
static void op_SC_CV_SLEW_get(const void *data, scene_state_t *ss,
                              exec_state_t *es, command_state_t *cs);
static void op_SC_CV_SET_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);
static void op_SC_CV_OFF_get(const void *data, scene_state_t *ss,
                             exec_state_t *es, command_state_t *cs);

const tele_op_t op_SC_TR = MAKE_GET_OP(SC.TR, op_SC_TR_get, 2, false);
const tele_op_t op_SC_TR_TOG =
    MAKE_GET_OP(SC.TR.TOG, op_SC_TR_TOG_get, 1, false);
const tele_op_t op_SC_TR_PULSE =
    MAKE_GET_OP(SC.TR.PULSE, op_SC_TR_PULSE_get, 1, false);
const tele_op_t op_SC_TR_TIME =
    MAKE_GET_OP(SC.TR.TIME, op_SC_TR_TIME_get, 2, false);
const tele_op_t op_SC_TR_POL =
    MAKE_GET_OP(SC.TR.POL, op_SC_TR_POL_get, 2, false);

const tele_op_t op_SC_TR_P =
    MAKE_ALIAS_OP(SC.TR.P, op_SC_TR_PULSE_get, NULL, 1, false);

const tele_op_t op_SC_CV = MAKE_GET_OP(SC.CV, op_SC_CV_get, 2, false);
const tele_op_t op_SC_CV_SLEW =
    MAKE_GET_OP(SC.CV.SLEW, op_SC_CV_SLEW_get, 2, false);
const tele_op_t op_SC_CV_SET =
    MAKE_GET_OP(SC.CV.SET, op_SC_CV_SET_get, 2, false);
const tele_op_t op_SC_CV_OFF =
    MAKE_GET_OP(SC.CV.OFF, op_SC_CV_OFF_get, 2, false);


void ERSend(uint8_t command, uint16_t output, int16_t value, bool set) {
    // zero-index the output
    output -= 1;
    // convert the output to the device and the port
    uint8_t port = output % 100;
    uint8_t device = output / 100;
    uint8_t address = ER301 + device;
    // put the package in the i2c mail
    SendIt(address, command, port, value, set);
}
void ERSet(uint8_t command, command_state_t *cs) {
    uint16_t output = cs_pop(cs);
    int16_t value = cs_pop(cs);
    ERSend(command, output, value, true);
}
void ERCommand(uint8_t command, uint16_t output) {
    ERSend(command, output, 0, false);
}


static void op_SC_TR_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_TR, cs);
}
static void op_SC_TR_TOG_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERCommand(TO_TR_TOG, cs_pop(cs));
}
static void op_SC_TR_PULSE_get(const void *NOTUSED(data), scene_state_t *ss,
                               exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERCommand(TO_TR_PULSE, cs_pop(cs));
}
static void op_SC_TR_TIME_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_TR_TIME, cs);
}
static void op_SC_TR_POL_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_TR_POL, cs);
}

static void op_SC_CV_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_CV, cs);
}
static void op_SC_CV_SLEW_get(const void *NOTUSED(data), scene_state_t *ss,
                              exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_CV_SLEW, cs);
}
static void op_SC_CV_SET_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_CV_SET, cs);
}
static void op_SC_CV_OFF_get(const void *NOTUSED(data), scene_state_t *ss,
                             exec_state_t *NOTUSED(es), command_state_t *cs) {
    ERSet(TO_CV_OFF, cs);
}