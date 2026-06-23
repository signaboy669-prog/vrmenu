#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/* VR Controller Menu Template */

typedef enum {
    BUTTON_A = 0,
    BUTTON_B = 1,
    BUTTON_X = 2,
    BUTTON_Y = 3,
    BUTTON_MENU = 4
} VRButton;

typedef enum {
    MENU_STATE_CLOSED = 0,
    MENU_STATE_OPENING = 1,
    MENU_STATE_OPEN = 2,
    MENU_STATE_CLOSING = 3
} MenuState;

typedef struct {
    float x, y, z;      /* 3D position */
    float rx, ry, rz;   /* Rotation (Euler) */
    float scale;        /* Menu scale (0.0 = closed, 1.0 = full) */
    MenuState state;
} VRMenu;

/* Initialize menu system */
void vr_menu_init(VRMenu* menu);

/* Handle button press for Y button hold */
void vr_menu_on_button_pressed(VRMenu* menu, VRButton button);
void vr_menu_on_button_released(VRMenu* menu, VRButton button);

/* Update menu state (call every frame) */
void vr_menu_update(VRMenu* menu, float delta_time);

/* Get current menu state */
MenuState vr_menu_get_state(VRMenu* menu);

/* Set menu position */
void vr_menu_set_position(VRMenu* menu, float x, float y, float z);

/* Get menu properties */
float vr_menu_get_scale(VRMenu* menu);
int vr_menu_is_visible(VRMenu* menu);

#ifdef __cplusplus
}
#endif
