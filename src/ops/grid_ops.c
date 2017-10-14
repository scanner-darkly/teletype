#include "ops/grid_ops.h"

#include "helpers.h"
#include "monome.h"
#include "teletype_io.h"

#define SG ss->grid
#define GB ss->grid.button[i]
#define GBC ss->grid.button[i].common
#define GF ss->grid.fader[i]
#define GFC ss->grid.fader[i].common
#define GXY ss->grid.xypad[i]
#define GXYC ss->grid.xypad[i].common

#define GET_AND_CLAMP(value, min, max) \
    s16 value = cs_pop(cs);            \
    if (value < (min))                 \
        value = (min);                 \
    else if (value > (max))            \
        value = (max);

#define GET_LEVEL(level)    \
    s16 level = cs_pop(cs); \
    if (level < LED_OFF)    \
        level = LED_OFF;    \
    else if (level > 15)    \
        level = 15;

static void grid_common_init(grid_common_t *gc);
static s16 scale(s16 a, s16 b, s16 x, s16 y, s16 value);

// clang-format off

static void op_G_RST_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_ROTATE_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_DIM_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_CLR_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_GRP_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_EN_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_RST_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_SW_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRP_SC_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GRPI_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_LED_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_LED_C_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_REC_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_BTN_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTX_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_EN_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_V_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_V_set  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_L_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNI_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNV_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTNL_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_BTN_SW_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GBTN_V_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GBTN_L_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_FDR_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDX_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDR_EN_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDR_V_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDR_V_set  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDR_N_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDR_N_set  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDR_L_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDRI_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDRV_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDRN_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_FDRL_get   (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GFDR_V_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GFDR_N_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GFDR_L_get (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_GFDR_RN_get(const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

static void op_G_XYP_get    (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_XYP_X_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);
static void op_G_XYP_Y_get  (const void *data, scene_state_t *ss, exec_state_t *es,  command_state_t *cs);

const tele_op_t op_G_RST     = MAKE_GET_OP(G.RST, op_G_RST_get, 0, false);
const tele_op_t op_G_ROTATE  = MAKE_GET_OP(G.ROTATE, op_G_ROTATE_get, 1, false);
const tele_op_t op_G_DIM     = MAKE_GET_OP(G.DIM, op_G_DIM_get, 1, false);
const tele_op_t op_G_CLR     = MAKE_GET_OP(G.CLR, op_G_CLR_get, 0, false);

const tele_op_t op_G_GRP     = MAKE_GET_OP(G.GRP, op_G_GRP_get, 1, false);
const tele_op_t op_G_GRP_EN  = MAKE_GET_OP(G.GRP.EN, op_G_GRP_EN_get, 2, false);
const tele_op_t op_G_GRP_RST = MAKE_GET_OP(G.GRP.RST, op_G_GRP_RST_get, 1, false);
const tele_op_t op_G_GRP_SW  = MAKE_GET_OP(G.GRP.SW, op_G_GRP_SW_get, 1, false);
const tele_op_t op_G_GRP_SC  = MAKE_GET_OP(G.GRP.SC, op_G_GRP_SC_get, 2, false);
const tele_op_t op_G_GRPI    = MAKE_GET_OP(G.GRPI, op_G_GRPI_get, 1, true);

const tele_op_t op_G_LED     = MAKE_GET_OP(G.LED, op_G_LED_get, 3, false);
const tele_op_t op_G_LED_C   = MAKE_GET_OP(G.LED.C, op_G_LED_C_get, 2, false);
const tele_op_t op_G_REC     = MAKE_GET_OP(G.REC, op_G_REC_get, 6, false);

const tele_op_t op_G_BTN     = MAKE_GET_OP(G.BTN, op_G_BTN_get, 8, false);
const tele_op_t op_G_BTX     = MAKE_GET_OP(G.BTX, op_G_BTX_get, 10, false);
const tele_op_t op_G_BTN_EN  = MAKE_GET_OP(G.BTN.EN, op_G_BTN_EN_get, 2, false);
const tele_op_t op_G_BTN_V   = MAKE_GET_SET_OP(G.BTN.V, op_G_BTN_V_get, op_G_BTN_V_set, 1, true);
const tele_op_t op_G_BTN_L   = MAKE_GET_OP(G.BTN.L, op_G_BTN_L_get, 2, false);
const tele_op_t op_G_BTNI    = MAKE_GET_OP(G.BTNI, op_G_BTNI_get, 0, true);
const tele_op_t op_G_BTNV    = MAKE_GET_OP(G.BTNV, op_G_BTNV_get, 0, true);
const tele_op_t op_G_BTNL    = MAKE_GET_OP(G.BTNL, op_G_BTNL_get, 1, false);
const tele_op_t op_G_BTN_SW  = MAKE_GET_OP(G.BTN.SW, op_G_BTN_SW_get, 1, false);
const tele_op_t op_G_GBTN_V  = MAKE_GET_OP(G.GBTN.V, op_G_GBTN_V_get, 2, false);
const tele_op_t op_G_GBTN_L  = MAKE_GET_OP(G.GBTN.L, op_G_GBTN_L_get, 3, false);

const tele_op_t op_G_FDR     = MAKE_GET_OP(G.FDR, op_G_FDR_get, 8, false);
const tele_op_t op_G_FDX     = MAKE_GET_OP(G.FDX, op_G_FDX_get, 10, false);
const tele_op_t op_G_FDR_EN  = MAKE_GET_OP(G.FDR.EN, op_G_FDR_EN_get, 2, false);
const tele_op_t op_G_FDR_V   = MAKE_GET_SET_OP(G.FDR.V, op_G_FDR_V_get, op_G_FDR_V_set, 1, true);
const tele_op_t op_G_FDR_N   = MAKE_GET_SET_OP(G.FDR.N, op_G_FDR_N_get, op_G_FDR_N_set, 1, true);
const tele_op_t op_G_FDR_L   = MAKE_GET_OP(G.FDR.L, op_G_FDR_L_get, 2, false);
const tele_op_t op_G_FDRI    = MAKE_GET_OP(G.FDRI, op_G_FDRI_get, 0, false);
const tele_op_t op_G_FDRV    = MAKE_GET_OP(G.FDRV, op_G_FDRV_get, 0, false);
const tele_op_t op_G_FDRN    = MAKE_GET_OP(G.FDRN, op_G_FDRN_get, 0, false);
const tele_op_t op_G_FDRL    = MAKE_GET_OP(G.FDRL, op_G_FDRL_get, 1, true);
const tele_op_t op_G_GFDR_V  = MAKE_GET_OP(G.GFDR.V, op_G_GFDR_V_get, 2, false);
const tele_op_t op_G_GFDR_N  = MAKE_GET_OP(G.GFDR.N, op_G_GFDR_N_get, 2, false);
const tele_op_t op_G_GFDR_L  = MAKE_GET_OP(G.GFDR.L, op_G_GFDR_L_get, 3, false);
const tele_op_t op_G_GFDR_RN = MAKE_GET_OP(G.GFDR.RN, op_G_GFDR_RN_get, 3, false);

const tele_op_t op_G_XYP     = MAKE_GET_OP(G.XYP, op_G_XYP_get, 7, false);
const tele_op_t op_G_XYP_X   = MAKE_GET_OP(G.XYP.X, op_G_XYP_X_get, 1, true);
const tele_op_t op_G_XYP_Y   = MAKE_GET_OP(G.XYP.Y, op_G_XYP_Y_get, 1, true);

// clang-format on

static void op_G_RST_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *NOTUSED(cs)) {
    SG.rotate = 0;
    SG.dim = 0;
    
    SG.current_group = 0;
    SG.latest_group = 0;
    SG.latest_button = 0;
    SG.latest_fader = 0;
    
    for (u8 i = 0; i < GRID_MAX_DIMENSION; i++)
        for (u8 j = 0; j < GRID_MAX_DIMENSION; j++)
            SG.leds[i][j] = LED_OFF;

    for (u8 i = 0; i < GRID_GROUP_COUNT; i++) {
        SG.group[i].enabled = true;
        SG.group[i].script = -1;
        SG.group[i].fader_min = 0;
        SG.group[i].fader_max = 16383;
    }
    
    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++) {
        grid_common_init(&(GBC));
        GB.latch = 0;
        GB.state = 0;
    }

    for (u8 i = 0; i < GRID_FADER_COUNT; i++) {
        grid_common_init(&(GFC));
        GF.dir = 0;
        GF.value = 0;
    }
    
    for (u8 i = 0; i < GRID_XYPAD_COUNT; i++) {
        grid_common_init(&(GXYC));
        GXY.value_x = 0;
        GXY.value_y = 0;
    }
    
    SG.refresh = true;
}

static void op_G_CLR_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *NOTUSED(cs)) {
    for (u8 i = 0; i < GRID_MAX_DIMENSION; i++)
        for (u8 j = 0; j < GRID_MAX_DIMENSION; j++)
            SG.leds[i][j] = LED_OFF;
    SG.refresh = true;
}

static void op_G_ROTATE_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 rotate = cs_pop(cs);
    SG.rotate = rotate;
    SG.refresh = true;
}

static void op_G_DIM_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    GET_AND_CLAMP(dim, 0, 14);
    SG.dim = dim;
    SG.refresh = true;
}

static void op_G_GRP_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    SG.current_group = group;
}

static void op_G_GRP_EN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    s16 en = cs_pop(cs);
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    SG.group[group].enabled = en;
    SG.refresh = true;
}

static void op_G_GRP_RST_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    
    SG.group[group].enabled = true;
    SG.group[group].script = -1;
    SG.group[group].fader_min = 0;
    SG.group[group].fader_max = 0;
    
    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == group) {
            grid_common_init(&(GBC));
            GB.latch = 0;
            GB.state = 0;
        }

    for (u8 i = 0; i < GRID_FADER_COUNT; i++)
        if (GFC.group == group) {
            grid_common_init(&(GFC));
            GF.dir = 0;
            GF.value = 0;
        }
    
    for (u8 i = 0; i < GRID_XYPAD_COUNT; i++)
        if (GXYC.group == group) {
            grid_common_init(&(GXYC));
            GXY.value_x = 0;
            GXY.value_y = 0;
        }
    
    SG.refresh = true;
}

static void op_G_GRP_SW_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    
    for (u8 i = 0; i < GRID_GROUP_COUNT; i++) SG.group[i].enabled = false;
    SG.group[group].enabled = true;
    
    SG.refresh = true;
}

static void op_G_GRP_SC_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    s16 script = cs_pop(cs) - 1;
    
    if (group < 0 || group >= GRID_BUTTON_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    SG.group[group].script = script;
}

static void op_G_GRPI_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.latest_group);
}

static void op_G_LED_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    GET_LEVEL(level);

    if (x < 0 || x >= GRID_MAX_DIMENSION) return;
    if (y < 0 || y >= GRID_MAX_DIMENSION) return;
    
    SG.leds[x][y] = level;
    SG.refresh = true;
}

static void op_G_LED_C_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);

    if (x < 0 || x >= GRID_MAX_DIMENSION) return;
    if (y < 0 || y >= GRID_MAX_DIMENSION) return;
    
    SG.leds[x][y] = LED_OFF;
    SG.refresh = true;
}

static void op_G_REC_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    GET_LEVEL(fill);
    GET_LEVEL(border);
    
    for (s16 col = max(0, x + 1); col < min(GRID_MAX_DIMENSION, x + w - 1); col++)
        for (s16 row = max(0, y + 1); row < min(GRID_MAX_DIMENSION, y + h - 1); row++)
            SG.leds[col][row] = fill;

    if (y >= 0 && y < GRID_MAX_DIMENSION)
        for (s16 col = max(0, x); col < min(GRID_MAX_DIMENSION, x + w); col++)
            SG.leds[col][y] = border;
        
    s16 row = y + h - 1;
    if (row >= 0 && row < GRID_MAX_DIMENSION)
        for (s16 col = max(0, x); col < min(GRID_MAX_DIMENSION, x + w); col++)
            SG.leds[col][row] = border;

    if (x >= 0 && x < GRID_MAX_DIMENSION)
        for (s16 row = max(0, y); row < min(GRID_MAX_DIMENSION, y + h); row++)
            SG.leds[x][row] = border;

    s16 col = x + w - 1;
    if (col >= 0 && col < GRID_MAX_DIMENSION)
        for (s16 row = max(0, y); row < min(GRID_MAX_DIMENSION, y + h); row++)
            SG.leds[col][row] = border;

    SG.refresh = true;
}

static void op_G_BTN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    s16 latch = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    GBC.enabled = true;
    GBC.group = SG.current_group;
    GBC.x = x;
    GBC.y = y;
    GBC.w = w;
    GBC.h = h;
    GBC.background = level;
    GBC.script = script;
    GB.latch = latch != 0;
    // GB.state = 0;
    
    SG.refresh = 1;
}

static void op_G_BTX_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 id = cs_pop(cs);
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    s16 latch = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    s16 count_x = cs_pop(cs);
    s16 count_y = cs_pop(cs);
    
    if (id < 0 || id >= GRID_BUTTON_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    if (count_x <= 0) return;
    if (count_x > 16) count_x = 16;
    if (count_y <= 0) return;
    if (count_y > 16) count_y = 16;
    
    u16 i;
    for (u16 cy = 0; cy < count_y; cy++)
        for (u16 cx = 0; cx < count_x; cx++) {
            i = id + cy * count_x + cx;
            if (i >= GRID_BUTTON_COUNT) break;
            GBC.enabled = true;
            GBC.group = SG.current_group;
            GBC.x = x + w * cx;
            GBC.y = y + h * cy;
            GBC.w = w;
            GBC.h = h;
            GBC.background = level;
            GBC.script = script;
            GB.latch = latch != 0;
            // GB.state = 0;
        }
    
    SG.refresh = 1;
}

static void op_G_BTN_EN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 en = cs_pop(cs);
    
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    GBC.enabled = en;
    SG.refresh = 1;
}

static void op_G_BTN_V_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    cs_push(cs, i < 0 || i >= GRID_BUTTON_COUNT ? 0 : GB.state);
}

static void op_G_BTN_V_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 value = cs_pop(cs);
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    GB.state = value != 0;
    SG.refresh = 1;
}

static void op_G_BTN_L_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    GET_LEVEL(level);
    if (i < 0 || i >= GRID_BUTTON_COUNT) return;
    GBC.background = level;
    SG.refresh = 1;
}

static void op_G_BTNI_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.latest_button);
}

static void op_G_BTNV_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.button[SG.latest_button].state);
}

static void op_G_BTNL_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    GET_LEVEL(level);
    SG.button[SG.latest_button].common.background = level;
    SG.refresh = 1;
}

static void op_G_BTN_SW_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 id = cs_pop(cs);
    if (id < 0 || id >= GRID_BUTTON_COUNT) return;
    
    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == SG.button[id].common.group) GB.state = 0;
    
    SG.button[id].state = 1;
    SG.refresh = 1;
}

static void op_G_GBTN_V_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    s16 value = cs_pop(cs);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;
    value = value != 0;

    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == group) GB.state = value;
    SG.refresh = 1;
}

static void op_G_GBTN_L_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    GET_LEVEL(odd);
    GET_LEVEL(even);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;

    u8 is_odd = 1;
    for (u16 i = 0; i < GRID_BUTTON_COUNT; i++)
        if (GBC.group == group) {
            GBC.background = is_odd ? odd : even;
            is_odd = !is_odd;
        }
    SG.refresh = 1;
}

static void op_G_FDR_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    s16 dir = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    
    if (i < 0 || i >= GRID_FADER_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    GFC.enabled = true;
    GFC.group = SG.current_group;
    GFC.x = x;
    GFC.y = y;
    GFC.w = w;
    GFC.h = h;
    GFC.background = level;
    GFC.script = script;
    GF.dir = dir != 0;
    // GF.value = 0;
    
    SG.refresh = 1;
}

static void op_G_FDX_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 id = cs_pop(cs);
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    s16 dir = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    s16 count_x = cs_pop(cs);
    s16 count_y = cs_pop(cs);
    
    if (id < 0 || id >= GRID_FADER_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    if (count_x <= 0) return;
    if (count_x > 16) count_x = 16;
    if (count_y <= 0) return;
    if (count_y > 16) count_y = 16;
    
    u16 i;
    for (u16 cy = 0; cy < count_y; cy++)
        for (u16 cx = 0; cx < count_x; cx++) {
            i = id + cy * count_x + cx;
            if (i >= GRID_FADER_COUNT) break;
            GFC.enabled = true;
            GFC.group = SG.current_group;
            GFC.x = x + w * cx;
            GFC.y = y + h * cy;
            GFC.w = w;
            GFC.h = h;
            GFC.background = level;
            GFC.script = script;
            GF.dir = dir != 0;
            // GF.value = 0;
        }
    
    SG.refresh = 1;
}

static void op_G_FDR_EN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 en = cs_pop(cs);
    
    if (i < 0 || i >= GRID_FADER_COUNT) return;
    GFC.enabled = en;
    SG.refresh = 1;
}

static void op_G_FDR_V_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    if (i < 0 || i >= GRID_FADER_COUNT) {
        cs_push(cs, 0);
        return;
    }
    
    s16 value = scale(0, GF.dir ? GFC.h - 1 : GFC.w - 1, SG.group[GFC.group].fader_min,
        SG.group[GFC.group].fader_max, GF.value);
    cs_push(cs, value);
}

static void op_G_FDR_V_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 value = cs_pop(cs);
    
    if (i < 0 || i >= GRID_FADER_COUNT) return;
    if (value < SG.group[GFC.group].fader_min) value = SG.group[GFC.group].fader_min;
    else if (value > SG.group[GFC.group].fader_max) value = SG.group[GFC.group].fader_max;
    
    GF.value = scale(SG.group[GFC.group].fader_min, 
        SG.group[GFC.group].fader_max, 0, GF.dir ? GFC.h - 1 : GFC.w - 1, value);
    SG.refresh = 1;
}

static void op_G_FDR_N_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    cs_push(cs, i < 0 || i >= GRID_FADER_COUNT ? 1 : GF.value + 1);
}

static void op_G_FDR_N_set(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 value = cs_pop(cs) - 1;
    
    if (i < 0 || i >= GRID_FADER_COUNT) return;
    if (value < 0) value = 0;
    else if (GF.dir && value >= GFC.h) value = GFC.h - 1;
    else if (!GF.dir && value >= GFC.w) value = GFC.w - 1;
    
    GF.value = value;
    SG.refresh = 1;
}

static void op_G_FDR_L_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    GET_LEVEL(level);
    if (i < 0 || i >= GRID_FADER_COUNT) return;
    GFC.background = level;
    SG.refresh = 1;
}

static void op_G_FDRI_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.latest_fader);
}

static void op_G_FDRV_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    u8 i = SG.latest_fader;
    s16 value = scale(0, GF.dir ? GFC.h - 1 : GFC.w - 1, SG.group[GFC.group].fader_min,
        SG.group[GFC.group].fader_max, GF.value);
    cs_push(cs, value);
}

static void op_G_FDRN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    cs_push(cs, SG.fader[SG.latest_fader].value);
}

static void op_G_FDRL_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    GET_LEVEL(level);
    SG.fader[SG.latest_fader].common.background = level;
    SG.refresh = 1;
}

static void op_G_GFDR_V_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    s16 value = cs_pop(cs);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;
    if (value < SG.group[group].fader_min) value = SG.group[group].fader_min;
    else if (value > SG.group[group].fader_max) value = SG.group[group].fader_max;

    for (u16 i = 0; i < GRID_FADER_COUNT; i++)
        if (GFC.group == group)
            GF.value = scale(SG.group[group].fader_min,
                SG.group[group].fader_max, 0, GF.dir ? GFC.h - 1 : GFC.w - 1, value);
                
    SG.refresh = 1;
}

static void op_G_GFDR_N_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    s16 value = cs_pop(cs) - 1;
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;
    if (value < 0) value = 0;

    for (u16 i = 0; i < GRID_FADER_COUNT; i++)
        if (GFC.group == group) GF.value = min(GF.dir ? GFC.h - 1 : GFC.w - 1, value);
    SG.refresh = 1;
}

static void op_G_GFDR_L_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    GET_LEVEL(odd);
    GET_LEVEL(even);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;

    u8 is_odd = 1;
    for (u16 i = 0; i < GRID_FADER_COUNT; i++)
        if (GFC.group == group) {
            GFC.background = is_odd ? odd : even;
            is_odd = !is_odd;
        }
    SG.refresh = 1;
}

static void op_G_GFDR_RN_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 group = cs_pop(cs);
    s16 min = cs_pop(cs);
    s16 max = cs_pop(cs);
    
    if (group < 0 || group > GRID_GROUP_COUNT) return;
    SG.group[group].fader_min = min;
    SG.group[group].fader_max = max;
}

static void op_G_XYP_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    s16 x = cs_pop(cs);
    s16 y = cs_pop(cs);
    s16 w = cs_pop(cs);
    s16 h = cs_pop(cs);
    GET_LEVEL(level);
    s16 script = cs_pop(cs) - 1;
    
    if (i < 0 || i >= GRID_XYPAD_COUNT) return;
    if (script < 0 || script > INIT_SCRIPT) script = -1;
    
    GXYC.enabled = true;
    GXYC.group = SG.current_group;
    GXYC.x = x;
    GXYC.y = y;
    GXYC.w = w;
    GXYC.h = h;
    GXYC.background = level;
    GXYC.script = script;
    GXY.value_x = 0;
    GXY.value_y = 0;
    
    SG.refresh = 1;
}

static void op_G_XYP_X_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    cs_push(cs, i < 0 || i >= GRID_XYPAD_COUNT ? 0 : GXY.value_x);
}

static void op_G_XYP_Y_get(const void *NOTUSED(data), scene_state_t *ss, exec_state_t *NOTUSED(es), command_state_t *cs) {
    s16 i = cs_pop(cs);
    cs_push(cs, i < 0 || i >= GRID_XYPAD_COUNT ? 0 : GXY.value_y);
}

void grid_common_init(grid_common_t *gc) {
    gc->enabled = false;
    gc->group = 0;
    gc->x = gc->y = 0;
    gc->w = gc->h = 1;
    gc->background = 5;
    gc->script = -1;
}

s16 scale(s16 a, s16 b, s16 x, s16 y, s16 value) {
    if (a == b) return x;
    return (value - a) * (y - x) / (b - a) + x;
}