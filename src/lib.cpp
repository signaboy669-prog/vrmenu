#include "lib.h"
#include <math.h>
#include <string.h>

/* VR Menu state machine with full menu item support */

static int y_button_held = 0;
static float open_progress = 0.0f;

void vr_menu_init(VRMenu* menu) {
    if (!menu) return;
    menu->x = 0.0f;
    menu->y = 0.0f;
    menu->z = -0.5f;
    menu->rx = 0.0f;
    menu->ry = 0.0f;
    menu->rz = 0.0f;
    menu->scale = 0.0f;
    menu->state = MENU_STATE_CLOSED;
    menu->item_count = 0;
    menu->selected_item = 0;
    menu->pointer_x = 0.0f;
    menu->pointer_y = 0.0f;
    menu->on_select = NULL;
    menu->on_back = NULL;
    y_button_held = 0;
    open_progress = 0.0f;
}

void vr_menu_on_button_pressed(VRMenu* menu, VRButton button) {
    if (!menu) return;
    
    if (button == BUTTON_Y) {
        if (!y_button_held) {
            y_button_held = 1;
            if (menu->state == MENU_STATE_CLOSED) {
                menu->state = MENU_STATE_OPENING;
            }
        }
    } else if (button == BUTTON_A && menu->state == MENU_STATE_OPEN) {
        /* Select current item */
        MenuItem* selected = vr_menu_get_selected_item(menu);
        if (selected && menu->on_select) {
            menu->on_select(selected);
        }
    } else if (button == BUTTON_B && menu->state == MENU_STATE_OPEN) {
        /* Back button closes or triggers callback */
        if (menu->on_back) {
            menu->on_back();
        }
        menu->state = MENU_STATE_CLOSING;
        y_button_held = 0;
    }
}

void vr_menu_on_button_released(VRMenu* menu, VRButton button) {
    if (!menu || button != BUTTON_Y) return;
    
    y_button_held = 0;
    if (menu->state == MENU_STATE_OPEN) {
        menu->state = MENU_STATE_CLOSING;
    }
}

void vr_menu_on_thumbstick(VRMenu* menu, float x, float y) {
    if (!menu || menu->state != MENU_STATE_OPEN) return;
    
    /* Navigate menu items with thumbstick Y */
    if (y > 0.5f && menu->selected_item > 0) {
        menu->selected_item--;
    } else if (y < -0.5f && menu->selected_item < menu->item_count - 1) {
        menu->selected_item++;
    }
    
    menu->pointer_x = x;
    menu->pointer_y = y;
}

void vr_menu_update(VRMenu* menu, float delta_time) {
    if (!menu) return;
    
    const float OPEN_SPEED = 2.5f;
    const float CLOSE_SPEED = 3.0f;
    
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

void vr_menu_set_rotation(VRMenu* menu, float rx, float ry, float rz) {
    if (!menu) return;
    menu->rx = rx;
    menu->ry = ry;
    menu->rz = rz;
}

float vr_menu_get_scale(VRMenu* menu) {
    return menu ? menu->scale : 0.0f;
}

int vr_menu_is_visible(VRMenu* menu) {
    return menu && menu->state != MENU_STATE_CLOSED;
}

int vr_menu_add_item(VRMenu* menu, int id, const char* label) {
    if (!menu || menu->item_count >= MAX_MENU_ITEMS) return -1;
    
    MenuItem* item = &menu->items[menu->item_count];
    item->id = id;
    item->label = label;
    item->selected = 0;
    
    return menu->item_count++;
}

void vr_menu_clear_items(VRMenu* menu) {
    if (!menu) return;
    menu->item_count = 0;
    menu->selected_item = 0;
}

MenuItem* vr_menu_get_selected_item(VRMenu* menu) {
    if (!menu || menu->selected_item < 0 || menu->selected_item >= menu->item_count) {
        return NULL;
    }
    return &menu->items[menu->selected_item];
}

int vr_menu_get_item_count(VRMenu* menu) {
    return menu ? menu->item_count : 0;
}

void vr_menu_set_select_callback(VRMenu* menu, void (*callback)(MenuItem* item)) {
    if (menu) menu->on_select = callback;
}

void vr_menu_set_back_callback(VRMenu* menu, void (*callback)(void)) {
    if (menu) menu->on_back = callback;
}
