# VR Menu Template Library

A C++ shared library for VR controller menu systems with holdable Y-button interaction.

## Features

- **VR Menu State Machine**: Open/Close/Opening/Closing states
- **Y-Button Hold Detection**: Menu opens while Y button is held, closes on release
- **Smooth Animation**: Configurable open/close speeds with scale transitions
- **Position & Rotation**: Set menu position relative to player
- **Cross-platform**: Builds on Windows (.dll), Linux (.so), and macOS

## API

```c
/* Initialize menu */
void vr_menu_init(VRMenu* menu);

/* Button input handling */
void vr_menu_on_button_pressed(VRMenu* menu, VRButton button);
void vr_menu_on_button_released(VRMenu* menu, VRButton button);

/* Update each frame with delta time */
void vr_menu_update(VRMenu* menu, float delta_time);

/* Query menu state */
MenuState vr_menu_get_state(VRMenu* menu);
float vr_menu_get_scale(VRMenu* menu);
int vr_menu_is_visible(VRMenu* menu);

/* Set menu position */
void vr_menu_set_position(VRMenu* menu, float x, float y, float z);
```

## Build

Builds automatically via GitHub Actions on every push:
- Windows: `mylib.dll`
- Linux: `libmylib.so`

Download artifacts from the [Actions](../../actions) tab.

## Example

```cpp
VRMenu menu;
vr_menu_init(&menu);

// Each frame:
vr_menu_update(&menu, delta_time);

// On button input:
if (controller.button_pressed(VR_BUTTON_Y))
    vr_menu_on_button_pressed(&menu, BUTTON_Y);

if (controller.button_released(VR_BUTTON_Y))
    vr_menu_on_button_released(&menu, BUTTON_Y);

// Render if visible:
if (vr_menu_is_visible(&menu)) {
    float scale = vr_menu_get_scale(&menu);
    // Render menu at menu->x,y,z with scale
}
```
