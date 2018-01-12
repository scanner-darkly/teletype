#include "ops/fader.h"

#include "helpers.h"
#include "ii.h"
#include "teletype.h"
#include "teletype_io.h"
#include "telex.h"


static void op_FADER_get(const void *data, scene_state_t *ss, exec_state_t *es,
                         command_state_t *cs);


const tele_op_t op_FADER = MAKE_GET_OP(FADER, op_FADER_get, 1, true);

const tele_op_t op_FB = MAKE_ALIAS_OP(FB, op_FADER_get, NULL, 1, true);


static void op_FADER_get(const void *NOTUSED(data), scene_state_t *ss,
                         exec_state_t *NOTUSED(es), command_state_t *cs) {
    uint16_t input = cs_pop(cs);
    // zero-index the input
    input -= 1;
    // return if out of range
    if (input < 0 || input > 15)
        return;
    // convert the input to the device and the port
    uint8_t port = input % 16;
    uint8_t device = input / 16;
    uint8_t address = FADER + device;
    ReceiveIt(address, port, cs);
}