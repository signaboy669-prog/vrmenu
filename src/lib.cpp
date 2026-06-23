#include "lib.h"
#include <math.h>

/* VR Menu state machine for holdable Y button menu */

static int y_button_held = 0;
static float open_progress = 0.0f;

void vr_menu_init(VRMenu* menu) {
    if (!menu) return;
    menu->x = 0.0f;
    menu->y = 0.0f;
    menu->z = -0.5f;  /* 0.5 units in front of player */
    menu->rx = 0.0f;
    menu->ry = 0.0f;
    menu->rz = 0.0f;
    menu->scale = 0.0f;
    menu->state = MENU_STATE_CLOSED;
    y_button_held = 0;
    open_progress = 0.0f;
}

void vr_menu_on_button_pressed(VRMenu* menu, VRButton button) {
    if (!menu || button != BUTTON_Y) return;
    
    if (!y_button_held) {
        y_button_held = 1;
        if (menu->state == MENU_STATE_CLOSED) {
            menu->state = MENU_STATE_OPENING;
        }
    }
}

void vr_menu_on_button_released(VRMenu* menu, VRButton button) {
    if (!menu || button != BUTTON_Y) return;
    
    y_button_held = 0;
    if (menu->state == MENU_STATE_OPEN) {
        menu->state = MENU_STATE_CLOSING;
    }
}

void vr_menu_update(VRMenu* menu, float delta_time) {
    if (!menu) return;
    
    const float OPEN_SPEED = 2.5f;  /* 2.5x speed */
    const float CLOSE_SPEED = 3.0f; /* 3.0x speed */
    
    switch (menu->state) {
        case MENU_STATE_OPENING:
            open_progress += delta_time * OPEN_SPEED;
            if (open_progress >= 1.0f) {
                open_progress = 1.0f;
                menu->state = MENU_STATE_OPEN;
            }
            menu->scale = open_progress;
            break;
            
        case MENU_STATE_CLOSING:
            open_progress -= delta_time * CLOSE_SPEED;
            if (open_progress <= 0.0f) {
                open_progress = 0.0f;
                menu->state = MENU_STATE_CLOSED;
            }
            menu->scale = open_progress;
            break;
            
        case MENU_STATE_OPEN:
            menu->scale = 1.0f;
            if (!y_button_held) {
                menu->state = MENU_STATE_CLOSING;
            }
            break;
            
        case MENU_STATE_CLOSED:
            menu->scale = 0.0f;
            break;
    }
}

MenuState vr_menu_get_state(VRMenu* menu) {
    return menu ? menu->state : MENU_STATE_CLOSED;
}

void vr_menu_set_position(VRMenu* menu, float x, float y, float z) {
    if (!menu) return;
    menu->x = x;
    menu->y = y;
    menu->z = z;
}

float vr_menu_get_scale(VRMenu* menu) {
    return menu ? menu->scale : 0.0f;
}

int vr_menu_is_visible(VRMenu* menu) {
    return menu && menu->state != MENU_STATE_CLOSED;
}
