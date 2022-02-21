// clang-format off

#ifndef _OP_ENUM_H_
#define _OP_ENUM_H_

// This file has been autogenerated by 'utils/op_enums.py'

typedef enum {
    E_OP_A,
    E_OP_B,
    E_OP_C,
    E_OP_D,
    E_OP_DRUNK,
    E_OP_DRUNK_MAX,
    E_OP_DRUNK_MIN,
    E_OP_DRUNK_WRAP,
    E_OP_FLIP,
    E_OP_I,
    E_OP_O,
    E_OP_O_INC,
    E_OP_O_MAX,
    E_OP_O_MIN,
    E_OP_O_WRAP,
    E_OP_T,
    E_OP_TIME,
    E_OP_TIME_ACT,
    E_OP_LAST,
    E_OP_X,
    E_OP_Y,
    E_OP_Z,
    E_OP_J,
    E_OP_K,
    E_OP_INIT,
    E_OP_INIT_SCENE,
    E_OP_INIT_SCRIPT,
    E_OP_INIT_SCRIPT_ALL,
    E_OP_INIT_P,
    E_OP_INIT_P_ALL,
    E_OP_INIT_CV,
    E_OP_INIT_CV_ALL,
    E_OP_INIT_TR,
    E_OP_INIT_TR_ALL,
    E_OP_INIT_DATA,
    E_OP_INIT_TIME,
    E_OP_TURTLE,
    E_OP_TURTLE_X,
    E_OP_TURTLE_Y,
    E_OP_TURTLE_MOVE,
    E_OP_TURTLE_F,
    E_OP_TURTLE_FX1,
    E_OP_TURTLE_FY1,
    E_OP_TURTLE_FX2,
    E_OP_TURTLE_FY2,
    E_OP_TURTLE_SPEED,
    E_OP_TURTLE_DIR,
    E_OP_TURTLE_STEP,
    E_OP_TURTLE_BUMP,
    E_OP_TURTLE_WRAP,
    E_OP_TURTLE_BOUNCE,
    E_OP_TURTLE_SCRIPT,
    E_OP_TURTLE_SHOW,
    E_OP_M,
    E_OP_M_SYM_EXCLAMATION,
    E_OP_M_ACT,
    E_OP_M_RESET,
    E_OP_P_N,
    E_OP_P,
    E_OP_PN,
    E_OP_P_L,
    E_OP_PN_L,
    E_OP_P_WRAP,
    E_OP_PN_WRAP,
    E_OP_P_START,
    E_OP_PN_START,
    E_OP_P_END,
    E_OP_PN_END,
    E_OP_P_I,
    E_OP_PN_I,
    E_OP_P_HERE,
    E_OP_PN_HERE,
    E_OP_P_NEXT,
    E_OP_PN_NEXT,
    E_OP_P_PREV,
    E_OP_PN_PREV,
    E_OP_P_INS,
    E_OP_PN_INS,
    E_OP_P_RM,
    E_OP_PN_RM,
    E_OP_P_PUSH,
    E_OP_PN_PUSH,
    E_OP_P_POP,
    E_OP_PN_POP,
    E_OP_P_MIN,
    E_OP_PN_MIN,
    E_OP_P_MAX,
    E_OP_PN_MAX,
    E_OP_P_SHUF,
    E_OP_PN_SHUF,
    E_OP_P_REV,
    E_OP_PN_REV,
    E_OP_P_ROT,
    E_OP_PN_ROT,
    E_OP_P_RND,
    E_OP_PN_RND,
    E_OP_P_ADD,
    E_OP_PN_ADD,
    E_OP_P_SUB,
    E_OP_PN_SUB,
    E_OP_P_ADDW,
    E_OP_PN_ADDW,
    E_OP_P_SUBW,
    E_OP_PN_SUBW,
    E_OP_Q,
    E_OP_Q_AVG,
    E_OP_Q_N,
    E_OP_Q_CLR,
    E_OP_Q_GRW,
    E_OP_Q_SUM,
    E_OP_Q_MIN,
    E_OP_Q_MAX,
    E_OP_Q_RND,
    E_OP_Q_SRT,
    E_OP_Q_REV,
    E_OP_Q_SH,
    E_OP_Q_ADD,
    E_OP_Q_SUB,
    E_OP_Q_MUL,
    E_OP_Q_DIV,
    E_OP_Q_MOD,
    E_OP_Q_I,
    E_OP_Q_2P,
    E_OP_Q_P2,
    E_OP_CV,
    E_OP_CV_OFF,
    E_OP_CV_SLEW,
    E_OP_IN,
    E_OP_IN_SCALE,
    E_OP_PARAM,
    E_OP_PARAM_SCALE,
    E_OP_IN_CAL_MIN,
    E_OP_IN_CAL_MAX,
    E_OP_IN_CAL_RESET,
    E_OP_PARAM_CAL_MIN,
    E_OP_PARAM_CAL_MAX,
    E_OP_PARAM_CAL_RESET,
    E_OP_PRM,
    E_OP_TR,
    E_OP_TR_POL,
    E_OP_TR_TIME,
    E_OP_TR_TOG,
    E_OP_TR_PULSE,
    E_OP_TR_P,
    E_OP_CV_SET,
    E_OP_MUTE,
    E_OP_STATE,
    E_OP_DEVICE_FLIP,
    E_OP_LIVE_OFF,
    E_OP_LIVE_O,
    E_OP_LIVE_DASH,
    E_OP_LIVE_D,
    E_OP_LIVE_GRID,
    E_OP_LIVE_G,
    E_OP_LIVE_VARS,
    E_OP_LIVE_V,
    E_OP_PRINT,
    E_OP_PRT,
    E_OP_ADD,
    E_OP_SUB,
    E_OP_MUL,
    E_OP_DIV,
    E_OP_MOD,
    E_OP_RAND,
    E_OP_RND,
    E_OP_RRAND,
    E_OP_RRND,
    E_OP_R,
    E_OP_R_MIN,
    E_OP_R_MAX,
    E_OP_TOSS,
    E_OP_MIN,
    E_OP_MAX,
    E_OP_LIM,
    E_OP_WRAP,
    E_OP_WRP,
    E_OP_QT,
    E_OP_QT_S,
    E_OP_QT_CS,
    E_OP_QT_B,
    E_OP_QT_BX,
    E_OP_AVG,
    E_OP_EQ,
    E_OP_NE,
    E_OP_LT,
    E_OP_GT,
    E_OP_LTE,
    E_OP_GTE,
    E_OP_INR,
    E_OP_OUTR,
    E_OP_INRI,
    E_OP_OUTRI,
    E_OP_NZ,
    E_OP_EZ,
    E_OP_RSH,
    E_OP_LSH,
    E_OP_LROT,
    E_OP_RROT,
    E_OP_EXP,
    E_OP_ABS,
    E_OP_SGN,
    E_OP_AND,
    E_OP_OR,
    E_OP_AND3,
    E_OP_OR3,
    E_OP_AND4,
    E_OP_OR4,
    E_OP_JI,
    E_OP_SCALE,
    E_OP_SCL,
    E_OP_N,
    E_OP_VN,
    E_OP_HZ,
    E_OP_N_S,
    E_OP_N_C,
    E_OP_N_CS,
    E_OP_N_B,
    E_OP_N_BX,
    E_OP_V,
    E_OP_VV,
    E_OP_ER,
    E_OP_NR,
    E_OP_BPM,
    E_OP_BIT_OR,
    E_OP_BIT_AND,
    E_OP_BIT_NOT,
    E_OP_BIT_XOR,
    E_OP_BSET,
    E_OP_BGET,
    E_OP_BCLR,
    E_OP_BTOG,
    E_OP_BREV,
    E_OP_XOR,
    E_OP_CHAOS,
    E_OP_CHAOS_R,
    E_OP_CHAOS_ALG,
    E_OP_SYM_PLUS,
    E_OP_SYM_DASH,
    E_OP_SYM_STAR,
    E_OP_SYM_FORWARD_SLASH,
    E_OP_SYM_PERCENTAGE,
    E_OP_SYM_EQUAL_x2,
    E_OP_SYM_EXCLAMATION_EQUAL,
    E_OP_SYM_LEFT_ANGLED,
    E_OP_SYM_RIGHT_ANGLED,
    E_OP_SYM_LEFT_ANGLED_EQUAL,
    E_OP_SYM_RIGHT_ANGLED_EQUAL,
    E_OP_SYM_RIGHT_ANGLED_LEFT_ANGLED,
    E_OP_SYM_LEFT_ANGLED_RIGHT_ANGLED,
    E_OP_SYM_RIGHT_ANGLED_EQUAL_LEFT_ANGLED,
    E_OP_SYM_LEFT_ANGLED_EQUAL_RIGHT_ANGLED,
    E_OP_SYM_EXCLAMATION,
    E_OP_SYM_LEFT_ANGLED_x2,
    E_OP_SYM_RIGHT_ANGLED_x2,
    E_OP_SYM_LEFT_ANGLED_x3,
    E_OP_SYM_RIGHT_ANGLED_x3,
    E_OP_SYM_AMPERSAND_x2,
    E_OP_SYM_PIPE_x2,
    E_OP_SYM_AMPERSAND_x3,
    E_OP_SYM_PIPE_x3,
    E_OP_SYM_AMPERSAND_x4,
    E_OP_SYM_PIPE_x4,
    E_OP_TIF,
    E_OP_S_ALL,
    E_OP_S_POP,
    E_OP_S_CLR,
    E_OP_S_L,
    E_OP_SCRIPT,
    E_OP_SYM_DOLLAR,
    E_OP_SCRIPT_POL,
    E_OP_SYM_DOLLAR_POL,
    E_OP_KILL,
    E_OP_SCENE,
    E_OP_SCENE_G,
    E_OP_SCENE_P,
    E_OP_BREAK,
    E_OP_BRK,
    E_OP_SYNC,
    E_OP_DEL_CLR,
    E_OP_IIA,
    E_OP_IIS,
    E_OP_IIS1,
    E_OP_IIS2,
    E_OP_IIS3,
    E_OP_IISB1,
    E_OP_IISB2,
    E_OP_IISB3,
    E_OP_IIQ,
    E_OP_IIQ1,
    E_OP_IIQ2,
    E_OP_IIQ3,
    E_OP_IIQB1,
    E_OP_IIQB2,
    E_OP_IIQB3,
    E_OP_IIB,
    E_OP_IIB1,
    E_OP_IIB2,
    E_OP_IIB3,
    E_OP_IIBB1,
    E_OP_IIBB2,
    E_OP_IIBB3,
    E_OP_WW_PRESET,
    E_OP_WW_POS,
    E_OP_WW_SYNC,
    E_OP_WW_START,
    E_OP_WW_END,
    E_OP_WW_PMODE,
    E_OP_WW_PATTERN,
    E_OP_WW_QPATTERN,
    E_OP_WW_MUTE1,
    E_OP_WW_MUTE2,
    E_OP_WW_MUTE3,
    E_OP_WW_MUTE4,
    E_OP_WW_MUTEA,
    E_OP_WW_MUTEB,
    E_OP_MP_PRESET,
    E_OP_MP_RESET,
    E_OP_MP_STOP,
    E_OP_ES_PRESET,
    E_OP_ES_MODE,
    E_OP_ES_CLOCK,
    E_OP_ES_RESET,
    E_OP_ES_PATTERN,
    E_OP_ES_TRANS,
    E_OP_ES_STOP,
    E_OP_ES_TRIPLE,
    E_OP_ES_MAGIC,
    E_OP_ES_CV,
    E_OP_OR_TRK,
    E_OP_OR_CLK,
    E_OP_OR_DIV,
    E_OP_OR_PHASE,
    E_OP_OR_RST,
    E_OP_OR_WGT,
    E_OP_OR_MUTE,
    E_OP_OR_SCALE,
    E_OP_OR_BANK,
    E_OP_OR_PRESET,
    E_OP_OR_RELOAD,
    E_OP_OR_ROTS,
    E_OP_OR_ROTW,
    E_OP_OR_GRST,
    E_OP_OR_CVA,
    E_OP_OR_CVB,
    E_OP_ANS_G_LED,
    E_OP_ANS_G,
    E_OP_ANS_G_P,
    E_OP_ANS_A_LED,
    E_OP_ANS_A,
    E_OP_ANS_APP,
    E_OP_KR_PRE,
    E_OP_KR_PAT,
    E_OP_KR_SCALE,
    E_OP_KR_PERIOD,
    E_OP_KR_POS,
    E_OP_KR_L_ST,
    E_OP_KR_L_LEN,
    E_OP_KR_RES,
    E_OP_KR_CV,
    E_OP_KR_MUTE,
    E_OP_KR_TMUTE,
    E_OP_KR_CLK,
    E_OP_KR_PG,
    E_OP_KR_CUE,
    E_OP_KR_DIR,
    E_OP_KR_DUR,
    E_OP_ME_PRE,
    E_OP_ME_RES,
    E_OP_ME_STOP,
    E_OP_ME_SCALE,
    E_OP_ME_PERIOD,
    E_OP_ME_CV,
    E_OP_LV_PRE,
    E_OP_LV_RES,
    E_OP_LV_POS,
    E_OP_LV_L_ST,
    E_OP_LV_L_LEN,
    E_OP_LV_L_DIR,
    E_OP_LV_CV,
    E_OP_CY_PRE,
    E_OP_CY_RES,
    E_OP_CY_POS,
    E_OP_CY_REV,
    E_OP_CY_CV,
    E_OP_MID_SHIFT,
    E_OP_MID_SLEW,
    E_OP_ARP_STY,
    E_OP_ARP_HLD,
    E_OP_ARP_RPT,
    E_OP_ARP_GT,
    E_OP_ARP_DIV,
    E_OP_ARP_RES,
    E_OP_ARP_SHIFT,
    E_OP_ARP_SLEW,
    E_OP_ARP_FIL,
    E_OP_ARP_ROT,
    E_OP_ARP_ER,
    E_OP_JF_TR,
    E_OP_JF_RMODE,
    E_OP_JF_RUN,
    E_OP_JF_SHIFT,
    E_OP_JF_VTR,
    E_OP_JF_MODE,
    E_OP_JF_TICK,
    E_OP_JF_VOX,
    E_OP_JF_NOTE,
    E_OP_JF_GOD,
    E_OP_JF_TUNE,
    E_OP_JF_QT,
    E_OP_JF_PITCH,
    E_OP_JF_ADDR,
    E_OP_JF_SPEED,
    E_OP_JF_TSC,
    E_OP_JF_RAMP,
    E_OP_JF_CURVE,
    E_OP_JF_FM,
    E_OP_JF_TIME,
    E_OP_JF_INTONE,
    E_OP_JF_POLY,
    E_OP_JF_POLY_RESET,
    E_OP_JF_SEL,
    E_OP_WS_PLAY,
    E_OP_WS_REC,
    E_OP_WS_CUE,
    E_OP_WS_LOOP,
    E_OP_WS_S_PITCH,
    E_OP_WS_S_VEL,
    E_OP_WS_S_VOX,
    E_OP_WS_S_NOTE,
    E_OP_WS_S_AR_MODE,
    E_OP_WS_S_LPG_TIME,
    E_OP_WS_S_LPG_SYMMETRY,
    E_OP_WS_S_CURVE,
    E_OP_WS_S_RAMP,
    E_OP_WS_S_FM_INDEX,
    E_OP_WS_S_FM_RATIO,
    E_OP_WS_S_FM_ENV,
    E_OP_WS_S_VOICES,
    E_OP_WS_S_PATCH,
    E_OP_WS_D_FEEDBACK,
    E_OP_WS_D_MIX,
    E_OP_WS_D_LOWPASS,
    E_OP_WS_D_FREEZE,
    E_OP_WS_D_TIME,
    E_OP_WS_D_LENGTH,
    E_OP_WS_D_POSITION,
    E_OP_WS_D_CUT,
    E_OP_WS_D_FREQ_RANGE,
    E_OP_WS_D_RATE,
    E_OP_WS_D_FREQ,
    E_OP_WS_D_CLK,
    E_OP_WS_D_CLK_RATIO,
    E_OP_WS_D_PLUCK,
    E_OP_WS_D_MOD_RATE,
    E_OP_WS_D_MOD_AMOUNT,
    E_OP_WS_T_RECORD,
    E_OP_WS_T_PLAY,
    E_OP_WS_T_REV,
    E_OP_WS_T_SPEED,
    E_OP_WS_T_FREQ,
    E_OP_WS_T_PRE_LEVEL,
    E_OP_WS_T_MONITOR_LEVEL,
    E_OP_WS_T_REC_LEVEL,
    E_OP_WS_T_HEAD_ORDER,
    E_OP_WS_T_LOOP_START,
    E_OP_WS_T_LOOP_END,
    E_OP_WS_T_LOOP_ACTIVE,
    E_OP_WS_T_LOOP_SCALE,
    E_OP_WS_T_LOOP_NEXT,
    E_OP_WS_T_TIMESTAMP,
    E_OP_WS_T_SEEK,
    E_OP_WS_T_CLEARTAPE,
    E_OP_CROW_SEL,
    E_OP_CROW_V,
    E_OP_CROW_SLEW,
    E_OP_CROW_C1,
    E_OP_CROW_C2,
    E_OP_CROW_C3,
    E_OP_CROW_C4,
    E_OP_CROW_RST,
    E_OP_CROW_PULSE,
    E_OP_CROW_AR,
    E_OP_CROW_LFO,
    E_OP_CROW_IN,
    E_OP_CROW_OUT,
    E_OP_CROW_Q0,
    E_OP_CROW_Q1,
    E_OP_CROW_Q2,
    E_OP_CROW_Q3,
    E_OP_TO_TR,
    E_OP_TO_TR_TOG,
    E_OP_TO_TR_PULSE,
    E_OP_TO_TR_TIME,
    E_OP_TO_TR_TIME_S,
    E_OP_TO_TR_TIME_M,
    E_OP_TO_TR_POL,
    E_OP_TO_KILL,
    E_OP_TO_TR_PULSE_DIV,
    E_OP_TO_TR_PULSE_MUTE,
    E_OP_TO_TR_M_MUL,
    E_OP_TO_M,
    E_OP_TO_M_S,
    E_OP_TO_M_M,
    E_OP_TO_M_BPM,
    E_OP_TO_M_ACT,
    E_OP_TO_M_SYNC,
    E_OP_TO_M_COUNT,
    E_OP_TO_TR_M,
    E_OP_TO_TR_M_S,
    E_OP_TO_TR_M_M,
    E_OP_TO_TR_M_BPM,
    E_OP_TO_TR_M_ACT,
    E_OP_TO_TR_M_SYNC,
    E_OP_TO_TR_WIDTH,
    E_OP_TO_TR_M_COUNT,
    E_OP_TO_CV,
    E_OP_TO_CV_SLEW,
    E_OP_TO_CV_SLEW_S,
    E_OP_TO_CV_SLEW_M,
    E_OP_TO_CV_SET,
    E_OP_TO_CV_OFF,
    E_OP_TO_CV_QT,
    E_OP_TO_CV_QT_SET,
    E_OP_TO_CV_N,
    E_OP_TO_CV_N_SET,
    E_OP_TO_CV_SCALE,
    E_OP_TO_CV_LOG,
    E_OP_TO_CV_INIT,
    E_OP_TO_TR_INIT,
    E_OP_TO_INIT,
    E_OP_TO_TR_P,
    E_OP_TO_TR_P_DIV,
    E_OP_TO_TR_P_MUTE,
    E_OP_TO_OSC,
    E_OP_TO_OSC_SET,
    E_OP_TO_OSC_QT,
    E_OP_TO_OSC_QT_SET,
    E_OP_TO_OSC_FQ,
    E_OP_TO_OSC_FQ_SET,
    E_OP_TO_OSC_N,
    E_OP_TO_OSC_N_SET,
    E_OP_TO_OSC_LFO,
    E_OP_TO_OSC_LFO_SET,
    E_OP_TO_OSC_WAVE,
    E_OP_TO_OSC_SYNC,
    E_OP_TO_OSC_PHASE,
    E_OP_TO_OSC_WIDTH,
    E_OP_TO_OSC_RECT,
    E_OP_TO_OSC_SLEW,
    E_OP_TO_OSC_SLEW_S,
    E_OP_TO_OSC_SLEW_M,
    E_OP_TO_OSC_SCALE,
    E_OP_TO_OSC_CYC,
    E_OP_TO_OSC_CYC_S,
    E_OP_TO_OSC_CYC_M,
    E_OP_TO_OSC_CYC_SET,
    E_OP_TO_OSC_CYC_S_SET,
    E_OP_TO_OSC_CYC_M_SET,
    E_OP_TO_OSC_CTR,
    E_OP_TO_ENV_ACT,
    E_OP_TO_ENV_ATT,
    E_OP_TO_ENV_ATT_S,
    E_OP_TO_ENV_ATT_M,
    E_OP_TO_ENV_DEC,
    E_OP_TO_ENV_DEC_S,
    E_OP_TO_ENV_DEC_M,
    E_OP_TO_ENV_TRIG,
    E_OP_TO_ENV_EOR,
    E_OP_TO_ENV_EOC,
    E_OP_TO_ENV_LOOP,
    E_OP_TO_ENV,
    E_OP_TO_CV_CALIB,
    E_OP_TO_CV_RESET,
    E_OP_TI_PARAM,
    E_OP_TI_PARAM_QT,
    E_OP_TI_PARAM_N,
    E_OP_TI_PARAM_SCALE,
    E_OP_TI_PARAM_MAP,
    E_OP_TI_IN,
    E_OP_TI_IN_QT,
    E_OP_TI_IN_N,
    E_OP_TI_IN_SCALE,
    E_OP_TI_IN_MAP,
    E_OP_TI_PARAM_CALIB,
    E_OP_TI_IN_CALIB,
    E_OP_TI_STORE,
    E_OP_TI_RESET,
    E_OP_TI_PARAM_INIT,
    E_OP_TI_IN_INIT,
    E_OP_TI_INIT,
    E_OP_TI_PRM,
    E_OP_TI_PRM_QT,
    E_OP_TI_PRM_N,
    E_OP_TI_PRM_SCALE,
    E_OP_TI_PRM_MAP,
    E_OP_TI_PRM_CALIB,
    E_OP_TI_PRM_INIT,
    E_OP_FADER,
    E_OP_FADER_SCALE,
    E_OP_FADER_CAL_MIN,
    E_OP_FADER_CAL_MAX,
    E_OP_FADER_CAL_RESET,
    E_OP_FB,
    E_OP_FB_S,
    E_OP_FB_C_MIN,
    E_OP_FB_C_MAX,
    E_OP_FB_C_R,
    E_OP_SC_TR,
    E_OP_SC_TR_TOG,
    E_OP_SC_TR_PULSE,
    E_OP_SC_TR_TIME,
    E_OP_SC_TR_POL,
    E_OP_SC_CV,
    E_OP_SC_CV_SLEW,
    E_OP_SC_CV_SET,
    E_OP_SC_CV_OFF,
    E_OP_SC_TR_P,
    E_OP_G_RST,
    E_OP_G_CLR,
    E_OP_G_ROTATE,
    E_OP_G_DIM,
    E_OP_G_KEY,
    E_OP_G_GRP,
    E_OP_G_GRP_EN,
    E_OP_G_GRP_RST,
    E_OP_G_GRP_SW,
    E_OP_G_GRP_SC,
    E_OP_G_GRPI,
    E_OP_G_LED,
    E_OP_G_LED_C,
    E_OP_G_REC,
    E_OP_G_RCT,
    E_OP_G_BTN,
    E_OP_G_BTX,
    E_OP_G_GBT,
    E_OP_G_GBX,
    E_OP_G_BTN_EN,
    E_OP_G_BTN_V,
    E_OP_G_BTN_L,
    E_OP_G_BTN_X,
    E_OP_G_BTN_Y,
    E_OP_G_BTNI,
    E_OP_G_BTNV,
    E_OP_G_BTNL,
    E_OP_G_BTNX,
    E_OP_G_BTNY,
    E_OP_G_BTN_SW,
    E_OP_G_BTN_PR,
    E_OP_G_GBTN_V,
    E_OP_G_GBTN_L,
    E_OP_G_FDR,
    E_OP_G_FDX,
    E_OP_G_GFD,
    E_OP_G_GFX,
    E_OP_G_FDR_EN,
    E_OP_G_FDR_V,
    E_OP_G_FDR_N,
    E_OP_G_FDR_L,
    E_OP_G_FDR_X,
    E_OP_G_FDR_Y,
    E_OP_G_FDRI,
    E_OP_G_FDRV,
    E_OP_G_FDRN,
    E_OP_G_FDRL,
    E_OP_G_FDRX,
    E_OP_G_FDRY,
    E_OP_G_FDR_PR,
    E_OP_G_GFDR_V,
    E_OP_G_GFDR_N,
    E_OP_G_GFDR_L,
    E_OP_G_GFDR_RN,
    E_OP_G_XYP,
    E_OP_G_XYP_X,
    E_OP_G_XYP_Y,
    E_OP_G_GBTN_C,
    E_OP_G_GBTN_I,
    E_OP_G_GBTN_W,
    E_OP_G_GBTN_H,
    E_OP_G_GBTN_X1,
    E_OP_G_GBTN_X2,
    E_OP_G_GBTN_Y1,
    E_OP_G_GBTN_Y2,
    E_OP_MA_SELECT,
    E_OP_MA_STEP,
    E_OP_MA_RESET,
    E_OP_MA_PGM,
    E_OP_MA_ON,
    E_OP_MA_PON,
    E_OP_MA_OFF,
    E_OP_MA_POFF,
    E_OP_MA_SET,
    E_OP_MA_PSET,
    E_OP_MA_COL,
    E_OP_MA_PCOL,
    E_OP_MA_ROW,
    E_OP_MA_PROW,
    E_OP_MA_CLR,
    E_OP_MA_PCLR,
    E_OP_EX,
    E_OP_EX_PRESET,
    E_OP_EX_PRE,
    E_OP_EX_SAVE,
    E_OP_EX_RESET,
    E_OP_EX_ALG,
    E_OP_EX_A,
    E_OP_EX_CTRL,
    E_OP_EX_C,
    E_OP_EX_PARAM,
    E_OP_EX_P,
    E_OP_EX_PV,
    E_OP_EX_MIN,
    E_OP_EX_MAX,
    E_OP_EX_REC,
    E_OP_EX_PLAY,
    E_OP_EX_AL_P,
    E_OP_EX_AL_CLK,
    E_OP_EX_M_CH,
    E_OP_EX_M_N,
    E_OP_EX_M_NO,
    E_OP_EX_M_PB,
    E_OP_EX_M_CC,
    E_OP_EX_M_PRG,
    E_OP_EX_M_CLK,
    E_OP_EX_M_START,
    E_OP_EX_M_STOP,
    E_OP_EX_M_CONT,
    E_OP_EX_SB_CH,
    E_OP_EX_SB_N,
    E_OP_EX_SB_NO,
    E_OP_EX_SB_PB,
    E_OP_EX_SB_CC,
    E_OP_EX_SB_PRG,
    E_OP_EX_SB_CLK,
    E_OP_EX_SB_START,
    E_OP_EX_SB_STOP,
    E_OP_EX_SB_CONT,
    E_OP_EX_VOX_P,
    E_OP_EX_VP,
    E_OP_EX_VOX,
    E_OP_EX_V,
    E_OP_EX_VOX_O,
    E_OP_EX_VO,
    E_OP_EX_NOTE,
    E_OP_EX_N,
    E_OP_EX_NOTE_O,
    E_OP_EX_NO,
    E_OP_EX_ALLOFF,
    E_OP_EX_AO,
    E_OP_EX_T,
    E_OP_EX_TV,
    E_OP_EX_LP_REC,
    E_OP_EX_LP_PLAY,
    E_OP_EX_LP_REV,
    E_OP_EX_LP_DOWN,
    E_OP_EX_LP_CLR,
    E_OP_EX_LP,
    E_OP_EX_LP_DOWNQ,
    E_OP_EX_LP_REVQ,
    E_OP_I2M_CH,
    E_OP_I2M_TIME,
    E_OP_I2M_SHIFT,
    E_OP_I2M_NOTE,
    E_OP_I2M_N,
    E_OP_I2M_NOTE_O,
    E_OP_I2M_NO,
    E_OP_I2M_N2,
    E_OP_I2M_NO2,
    E_OP_I2M_C,
    E_OP_I2M_C_PUSH,
    E_OP_I2M_C_RM,
    E_OP_I2M_C_CLR,
    E_OP_I2M_C_L,
    E_OP_I2M_C_INV,
    E_OP_I2M_CC,
    E_OP_I2M_CC2,
    E_OP_I2M_CCV,
    E_OP_I2M_CCV2,
    E_OP_I2M_CC_OFF,
    E_OP_I2M_CC_SLEW,
    E_OP_I2M_CC_SET,
    E_OP_I2M_NRPN,
    E_OP_I2M_NRPN_OFF,
    E_OP_I2M_NRPN_SLEW,
    E_OP_I2M_NRPN_SET,
    E_OP_I2M_PRG,
    E_OP_I2M_PB,
    E_OP_I2M_AT,
    E_OP_I2M_CLK,
    E_OP_I2M_START,
    E_OP_I2M_STOP,
    E_OP_I2M_CONT,
    E_OP_I2M_Q_CH,
    E_OP_I2M_Q_LATCH,
    E_OP_I2M_Q_NOTE,
    E_OP_I2M_Q_N,
    E_OP_I2M_Q_VEL,
    E_OP_I2M_Q_V,
    E_OP_I2M_Q_CC,
    E_OP_I2M_Q_LCH,
    E_OP_I2M_Q_LN,
    E_OP_I2M_Q_LV,
    E_OP_I2M_Q_LO,
    E_OP_I2M_Q_LC,
    E_OP_I2M_Q_LCC,
    E_OP_SEED,
    E_OP_RAND_SEED,
    E_OP_SYM_RAND_SD,
    E_OP_SYM_R_SD,
    E_OP_TOSS_SEED,
    E_OP_SYM_TOSS_SD,
    E_OP_PROB_SEED,
    E_OP_SYM_PROB_SD,
    E_OP_DRUNK_SEED,
    E_OP_SYM_DRUNK_SD,
    E_OP_P_SEED,
    E_OP_SYM_P_SD,
    E_OP_MI_SYM_DOLLAR,
    E_OP_MI_LN,
    E_OP_MI_LNV,
    E_OP_MI_LV,
    E_OP_MI_LVV,
    E_OP_MI_LO,
    E_OP_MI_LC,
    E_OP_MI_LCC,
    E_OP_MI_LCCV,
    E_OP_MI_NL,
    E_OP_MI_N,
    E_OP_MI_NV,
    E_OP_MI_V,
    E_OP_MI_VV,
    E_OP_MI_OL,
    E_OP_MI_O,
    E_OP_MI_CL,
    E_OP_MI_C,
    E_OP_MI_CC,
    E_OP_MI_CCV,
    E_OP_MI_LCH,
    E_OP_MI_NCH,
    E_OP_MI_OCH,
    E_OP_MI_CCH,
    E_OP_MI_LE,
    E_OP_MI_CLKD,
    E_OP_MI_CLKR,
    E_OP__LENGTH,
} tele_op_idx_t;

typedef enum {
    E_MOD_IF,
    E_MOD_ELIF,
    E_MOD_ELSE,
    E_MOD_L,
    E_MOD_W,
    E_MOD_EVERY,
    E_MOD_EV,
    E_MOD_SKIP,
    E_MOD_OTHER,
    E_MOD_PROB,
    E_MOD_DEL,
    E_MOD_DEL_X,
    E_MOD_DEL_R,
    E_MOD_DEL_G,
    E_MOD_DEL_B,
    E_MOD_P_MAP,
    E_MOD_PN_MAP,
    E_MOD_S,
    E_MOD_EX1,
    E_MOD_EX2,
    E_MOD_EX3,
    E_MOD_EX4,
    E_MOD_JF0,
    E_MOD_JF1,
    E_MOD_JF2,
    E_MOD_CROWN,
    E_MOD_CROW1,
    E_MOD_CROW2,
    E_MOD_CROW3,
    E_MOD_CROW4,
    E_MOD__LENGTH,
} tele_mod_idx_t;

#endif
