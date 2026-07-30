#include "key.h"
#include "ti_msp_dl_config.h"

#define DEBOUNCE_TICKS  100 

typedef enum {
    KEY_STATE_RELEASE = 0, 
    KEY_STATE_PRESSING,
    KEY_STATE_PRESSED 
} KeyState_t;

typedef struct {
    uint32_t pin_mask;
    KeyState_t state;
    uint16_t timer;
    bool event_flag;
} Key_t;

static Key_t keys[2] = {
    {DL_GPIO_PIN_14, KEY_STATE_RELEASE, 0, false},
    {DL_GPIO_PIN_11, KEY_STATE_RELEASE, 0, false}
};


void Key_Scan(void) {
    for (int i = 0; i < 2; i++) {
        bool is_down = ((DL_GPIO_readPins(GPIOB, keys[i].pin_mask) & keys[i].pin_mask) == 0);

        switch (keys[i].state) {
            case KEY_STATE_RELEASE:
                if (is_down) {
                    keys[i].state = KEY_STATE_PRESSING;
                    keys[i].timer = 0;
                }
                break;

            case KEY_STATE_PRESSING:
                if (is_down) {
                    keys[i].timer++;
                    if (keys[i].timer > DEBOUNCE_TICKS) {
                        keys[i].state = KEY_STATE_PRESSED;
                        keys[i].event_flag = true;
                    }
                } else {
                    keys[i].state = KEY_STATE_RELEASE;
                }
                break;

            case KEY_STATE_PRESSED:
                if (!is_down) {
                    keys[i].state = KEY_STATE_RELEASE;
                }
                break;
        }
    }
}

bool Key0_IsPressed(void) {
    if (keys[0].event_flag) {
        keys[0].event_flag = false;
        return true;
    }
    return false;
}

bool Key1_IsPressed(void) {
    if (keys[1].event_flag) {
        keys[1].event_flag = false;
        return true;
    }
    return false;
}
