#ifndef _OPS_ER301_H_
#define _OPS_ER301_H_

#include "ops/op.h"

extern const tele_op_t op_SC_TR;
extern const tele_op_t op_SC_TR_TOG;
extern const tele_op_t op_SC_TR_PULSE;
extern const tele_op_t op_SC_TR_TIME;
extern const tele_op_t op_SC_TR_POL;

extern const tele_op_t op_SC_TR_P;

extern const tele_op_t op_SC_CV;
extern const tele_op_t op_SC_CV_SLEW;
extern const tele_op_t op_SC_CV_SET;
extern const tele_op_t op_SC_CV_OFF;

#define ER301 0xB0

void ERSend(uint8_t command, uint16_t output, int16_t value, bool set);
void ERSet(uint8_t command, command_state_t *cs);
void ERCommand(uint8_t command, uint16_t output);

// not using these defines
// using the ones from the telex to make
// testing super-easy

/*
#define SC_TR 0x00
#define SC_TR_TOG 0x01
#define SC_TR_TIME 0x02
#define SC_TR_PULSE 0x05
#define SC_TR_POL 0x06

#define SC_CV 0x10
#define SC_CV_SET 0x11
#define SC_CV_SLEW 0x12
#define SC_CV_OFF 0x15
*/

#endif