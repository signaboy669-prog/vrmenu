#pragma once
#ifdef __cplusplus
extern "C" {
#endif

/* VR Controller Menu Template - Fully Functional */

#define MAX_MENU_ITEMS 16

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
    int id;
    const char* label;
    int selected;
} MenuItem;

typedef struct {
    float x, y, z;      /* 3D position */
    float rx, ry, rz;   /* Rotation (Euler) */
    float scale;        /* Menu scale (0.0 = closed, 1.0 = full) */
    MenuState state;
    
    /* Menu items */
    MenuItem items[MAX_MENU_ITEMS];
    int item_count;
    int selected_item;
    
    /* Pointer/cursor position for menu interaction */
    float pointer_x, pointer_y;
    
    /* Callbacks */
    void (*on_select)(MenuItem* item);
    void (*on_back)(void);
} VRMenu;

/* Initialize menu system */
void vr_menu_init(VRMenu* menu);

/* Handle button press/release for Y button hold */
void vr_menu_on_button_pressed(VRMenu* menu, VRButton button);
void vr_menu_on_button_released(VRMenu* menu, VRButton button);

/* Handle thumb stick for menu navigation */
void vr_menu_on_thumbstick(VRMenu* menu, float x, float y);

/* Update menu state (call every frame) */
void vr_menu_update(VRMenu* menu, float delta_time);

/* Get current menu state */
MenuState vr_menu_get_state(VRMenu* menu);

/* Set menu position and rotation */
void vr_menu_set_position(VRMenu* menu, float x, float y, float z);
void vr_menu_set_rotation(VRMenu* menu, float rx, float ry, float rz);

/* Menu properties */
float vr_menu_get_scale(VRMenu* menu);
int vr_menu_is_visible(VRMenu* menu);

/* Menu item management */
int vr_menu_add_item(VRMenu* menu, int id, const char* label);
void vr_menu_clear_items(VRMenu* menu);
MenuItem* vr_menu_get_selected_item(VRMenu* menu);
int vr_menu_get_item_count(VRMenu* menu);

/* Set callbacks */
void vr_menu_set_select_callback(VRMenu* menu, void (*callback)(MenuItem* item));
void vr_menu_set_back_callback(VRMenu* menu, void (*callback)(void));

#ifdef __cplusplus
}
#endif
