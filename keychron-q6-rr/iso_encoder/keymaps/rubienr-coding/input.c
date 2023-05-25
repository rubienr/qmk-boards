/*
// tap dance input / double tap input

enum {
    TD_CLL,
    TD_CLR,
    TD_TG_L,
    TD_TG_R,
};
*/

// combo input

enum combo_events {
    CB_UE,
    CB_OE,
    CB_AE,
    CB_SZ,
    COMBO_LENGTH
};
uint16_t COMBO_LEN = COMBO_LENGTH;

const uint16_t PROGMEM ae_combo[] = {KC_A, KC_E, COMBO_END};
const uint16_t PROGMEM oe_combo[] = {KC_O, KC_E, COMBO_END};
const uint16_t PROGMEM ue_combo[] = {KC_U, KC_E, COMBO_END};
const uint16_t PROGMEM sz_combo[] = {KC_S, KC_Z, COMBO_END};
combo_t key_combos[] = {
    COMBO(ae_combo, DE_ADIA),
    COMBO(oe_combo, DE_ODIA),
    COMBO(ue_combo, DE_UDIA),
    COMBO(sz_combo, DE_SS),
};


// custom key codes

enum custom_keycodes_t {
    CK_UCIS = SAFE_RANGE,
};

// utf8 ucis input
const ucis_symbol_t ucis_symbol_table[] = UCIS_TABLE(
    UCIS_SYM("poop"        , 0x1F4A9),                // 💩
    UCIS_SYM("rofl"        , 0x1F923),                // 🤣
    UCIS_SYM("look"        , 0xCA0, 0x5F, 0xCA0), // ಠ_ಠ
    UCIS_SYM("extrakurz"   , 0x306),               // ​˘
    UCIS_SYM("doppelpunkt" , 0x02D0),                 // ​ ː​
    UCIS_SYM("sr" , 0x005c),                 // ​ ː​
    UCIS_SYM("srug"        , 0x00af, 0x005c, 0x005f, 0x0028, 0x30c4, 0x0029, 0x005f, 0x002f, 0x00af) // ¯\_(ツ)_/¯
);

void ucis_symbol_fallback (void) {
    send_unicode_string("💩");
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool lsft_depressed = false, rsft_depressed = false;
    static bool lctl_depressed = false, rctl_depressed = false;
    static bool lalt_depressed = false, ralt_depressed = false;
    static bool a_depressed = false, o_depressed = false, u_depressed = false;
    static bool s_depressed = false, e_depressed = false, z_depressed = false;

    switch (keycode) {
        // ----- UTF input mode

        case CK_UCIS:
            if (!record->event.pressed) ucis_start();
            break;

        // ----- umlauts

        case DE_A:
            a_depressed = record->event.pressed;
            break;
        case DE_O:
            o_depressed = record->event.pressed;
            break;
        case DE_U:
            u_depressed = record->event.pressed;
            break;
        case DE_S:
            s_depressed = record->event.pressed;
            break;
        case DE_E: // umlaut: ae, oe, ue --> ä, ö, ü; for example an a then e is more convenient that an a + e combo
            e_depressed = record->event.pressed;
            if (e_depressed) {
                if (a_depressed) {
                    unregister_code(DE_E);
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    register_code(DE_ADIA);
                    unregister_code(DE_ADIA);
                    return false;
                }
                if (o_depressed) {
                    unregister_code(DE_E);
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    register_code(DE_ODIA);
                    unregister_code(DE_ODIA);
                    return false;
                }
                if (u_depressed) {
                    unregister_code(DE_E);
                    register_code(KC_BSPC);
                    unregister_code(KC_BSPC);
                    register_code(DE_UDIA);
                    unregister_code(DE_UDIA);
                    return false;
                }
            }
            break;

        case DE_Z: // sz -> ß
            z_depressed = record->event.pressed;
            if (s_depressed && z_depressed) {
                unregister_code(DE_Z);
                register_code(KC_BSPC);
                unregister_code(KC_BSPC);
                register_code(DE_SS);
                unregister_code(DE_SS);
                return false;
            }
            break;

        // ----- parenthesis and brackets ({[]})

        case KC_LSFT: // rsft + lsft --> (
            lsft_depressed = record->event.pressed;
            if (lsft_depressed && rsft_depressed) {
                unregister_code16(KC_LSFT);
                unregister_code16(KC_RSFT);
                uprintf("(\n");
                register_code16(DE_LPRN);
                unregister_code16(DE_LPRN);
                return false;
            }
            break;
        case KC_RSFT: // lsft + rsft --> )
            rsft_depressed = record->event.pressed;
            if (lsft_depressed && rsft_depressed) {
                unregister_code16(KC_RSFT);
                unregister_code16(KC_LSFT);
                uprintf(")\n");
                register_code16(DE_RPRN);
                unregister_code16(DE_RPRN);
                return false;
            }
            break;

        case KC_LCTL: // rsft + lctl --> {
            lctl_depressed = record->event.pressed;
            if (rsft_depressed && lctl_depressed) {
                unregister_code(KC_LCTL);
                unregister_code(KC_RSFT);
                register_code16(DE_LCBR);
                unregister_code16(DE_LCBR);
                return false;
            }
            break;
        case KC_RCTL: // lsft + rclt --> }
            rctl_depressed = record->event.pressed;
            if (lsft_depressed && rctl_depressed) {
                unregister_code(KC_RCTL);
                unregister_code(KC_LSFT);
                register_code16(DE_RCBR);
                unregister_code16(DE_RCBR);
                return false;
            }
            break;

        case KC_LALT: // rsft + lalt --> [
            lalt_depressed = record->event.pressed;
            if (rsft_depressed && lalt_depressed) {
                unregister_code(KC_LALT);
                unregister_code(KC_RSFT);
                register_code16(DE_LBRC);
                unregister_code16(DE_LBRC);
                return false;
            }
            break;
        case KC_RALT: // lsft + ralt --> ]
            ralt_depressed = record->event.pressed;
            if (lsft_depressed && ralt_depressed) {
                unregister_code(KC_RALT);
                unregister_code(KC_LSFT);
                register_code16(DE_RBRC);
                unregister_code16(DE_RBRC);
                return false;
            }
            break;
    }
    return true;
}

/*
// tap dance input / double tap input

void dance_sftl_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_LSFT); }
    else {register_code(KC_CAPS); }
}

void dance_sftl_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_LSFT); }
    else { unregister_code(KC_CAPS); }
}

void dance_sftr_finished(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) { register_code16(KC_RSFT); }
    else { register_code(KC_CAPS); }
}

void dance_sftr_reset(qk_tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {  unregister_code16(KC_RSFT); }
    else { unregister_code(KC_CAPS); }
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_RSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sftl_finished, dance_sftl_reset),
    [TD_LSFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_sftr_finished, dance_sftr_reset),
};
*/
