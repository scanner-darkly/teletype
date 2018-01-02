#ifndef _KEYBOARD_HELPER_
#define _KEYBOARD_HELPER_

#include <stdbool.h>
#include <stdint.h>

// asf
#include "conf_usb_host.h"  // needed in order to include "usb_protocol_hid.h"
#include "usb_protocol_hid.h"

// small functions defined static inline, so that each compilation unit gets
// it's own copy and may inline (no LTO in gcc 4.4.7)

static inline bool no_mod(uint8_t mod) {
    return mod == HID_MODIFIER_NONE;
}

static inline bool mod_only_shift(uint8_t mod) {
    return mod == HID_MODIFIER_LEFT_SHIFT || mod == HID_MODIFIER_RIGHT_SHIFT ||
           mod == (HID_MODIFIER_LEFT_SHIFT | HID_MODIFIER_RIGHT_SHIFT);
}

static inline bool mod_only_ctrl(uint8_t mod) {
    return mod == HID_MODIFIER_LEFT_CTRL || mod == HID_MODIFIER_RIGHT_CTRL ||
           mod == (HID_MODIFIER_LEFT_CTRL | HID_MODIFIER_RIGHT_CTRL);
}

static inline bool mod_only_shift_ctrl(uint8_t mod) {
    const uint8_t either_sh =
        HID_MODIFIER_LEFT_SHIFT | HID_MODIFIER_RIGHT_SHIFT;
    const uint8_t either_ctrl =
        HID_MODIFIER_LEFT_CTRL | HID_MODIFIER_RIGHT_CTRL;
    // first check we only have shift and alt
    if (mod & ~(either_sh | either_ctrl)) return false;
    return (mod & either_sh) && (mod & either_ctrl);
}

static inline bool mod_only_alt(uint8_t mod) {
    return mod == HID_MODIFIER_LEFT_ALT || mod == HID_MODIFIER_RIGHT_ALT ||
           mod == (HID_MODIFIER_LEFT_ALT | HID_MODIFIER_RIGHT_ALT);
}

static inline bool mod_only_shift_alt(uint8_t mod) {
    const uint8_t either_sh =
        HID_MODIFIER_LEFT_SHIFT | HID_MODIFIER_RIGHT_SHIFT;
    const uint8_t either_alt = HID_MODIFIER_LEFT_ALT | HID_MODIFIER_RIGHT_ALT;
    // first check we only have shift and alt
    if (mod & ~(either_sh | either_alt)) return false;
    return (mod & either_sh) && (mod & either_alt);
}

static inline bool mod_only_win(uint8_t mod) {
    return mod == HID_MODIFIER_LEFT_UI || mod == HID_MODIFIER_RIGHT_UI ||
           mod == (HID_MODIFIER_LEFT_UI | HID_MODIFIER_RIGHT_UI);
}

static inline bool match_no_mod(uint8_t mod, uint8_t key,
                                uint8_t required_key) {
    return (mod == HID_MODIFIER_NONE) && (key == required_key);
}

static inline bool match_shift(uint8_t mod, uint8_t key, uint8_t required_key) {
    return mod_only_shift(mod) && key == required_key;
}

static inline bool match_ctrl(uint8_t mod, uint8_t key, uint8_t required_key) {
    return mod_only_ctrl(mod) && key == required_key;
}

static inline bool match_alt(uint8_t mod, uint8_t key, uint8_t required_key) {
    return mod_only_alt(mod) && key == required_key;
}

static inline bool match_shift_alt(uint8_t mod, uint8_t key,
                                   uint8_t required_key) {
    return mod_only_shift_alt(mod) && key == required_key;
}

static inline bool match_shift_ctrl(uint8_t mod, uint8_t key,
                                    uint8_t required_key) {
    return mod_only_shift_ctrl(mod) && key == required_key;
}

static inline bool match_win(uint8_t mod, uint8_t key, uint8_t required_key) {
    return mod_only_win(mod) && key == required_key;
}

#endif
