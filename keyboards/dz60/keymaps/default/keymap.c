#include QMK_KEYBOARD_H


#define SINS LSFT(KC_INS)
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    *  Esc 1   2   3   4   5   6   7   8   9   0   -   =   ~   \
    *  Tab   q   w   e   r   t   y   u   i   o   p   [   ]   Bspc
    *  LCtrl   a   s   d   f   g   h   j   k   l   ;   '   Enter
    *  LShft    z   x   c   v   b   n   m   ,   .   /   Rshft   Fn1
    *  LCtrl LGui  LAlt    Spc   Spc   Spc     RAlt RGui Menu RCtrl
    */
	KEYMAP_SCOTT(
		KC_ESC, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_GRV, KC_BSLS,
		KC_TAB,   KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC,  KC_BSPC,
		KC_CAPS,    KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT,   KC_ENT,
		KC_LSFT,      KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, MO(1),
		KC_CAPS, KC_LGUI, KC_LALT,      KC_SPC, MO(1), KC_SPC,       KC_RALT, KC_RGUI, KC_RGUI, KC_RCTL
    ),
	KEYMAP_SCOTT(
		KC_GRV, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_TRNS, RGB_M_G,
        SINS,   RGB_TOG, RGB_MOD, RGB_HUI, RGB_HUD, RGB_SAI, RGB_SAD, RGB_VAI, RGB_VAD,  RGB_M_B, RGB_M_R, KC_UP, RGB_M_SW, RGB_M_X,
		KC_TRNS,    KC_MUTE, KC_VOLD, KC_VOLU, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_HOME, KC_PGUP, KC_LEFT, KC_RGHT,   KC_TRNS,
		KC_TRNS,      KC_MPLY, KC_MPRV, KC_MNXT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_END, KC_PGDN, KC_DOWN, KC_TRNS, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_TRNS,      KC_TRNS, KC_TRNS, KC_TRNS,       KC_TRNS, KC_TRNS, MO(2), KC_TRNS
    ),
};

enum function_id {
    SHIFT_ESC,
};

const uint16_t PROGMEM fn_actions[] = {
  [0]  = ACTION_FUNCTION(SHIFT_ESC),
};

void action_function(keyrecord_t *record, uint8_t id, uint8_t opt) {
  static uint8_t shift_esc_shift_mask;
  switch (id) {
    case SHIFT_ESC:
      shift_esc_shift_mask = get_mods()&MODS_CTRL_MASK;
      if (record->event.pressed) {
        if (shift_esc_shift_mask) {
          add_key(KC_GRV);
          send_keyboard_report();
        } else {
          add_key(KC_ESC);
          send_keyboard_report();
        }
      } else {
        if (shift_esc_shift_mask) {
          del_key(KC_GRV);
          send_keyboard_report();
        } else {
          del_key(KC_ESC);
          send_keyboard_report();
        }
      }
      break;
  }
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1 << USB_LED_CAPS_LOCK)) {
        DDRB |= (1 << 2); PORTB &= ~(1 << 2);
    } else {
        DDRB &= ~(1 << 2); PORTB &= ~(1 << 2);
    }
}
