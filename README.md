# VR Menu Template Library

A fully functional C++ shared library for VR controller menu systems with holdable Y-button interaction, menu item selection, and state management.

## Features ✨

- **Holdable Y-Button Menu**: Hold Y to open, release to close with smooth animations
- **Menu Item Management**: Add up to 16 items, navigate with thumbstick
- **Button Interaction**: 
  - Y: Open/close menu
  - A: Select highlighted item
  - B: Back/cancel
- **Thumbstick Navigation**: Move up/down to select menu items
- **Callbacks**: Custom callbacks for item selection and back action
- **State Machine**: Open/Close/Opening/Closing states with smooth transitions
- **Position & Rotation**: Full 3D positioning relative to player
- **Cross-platform**: Windows (.dll), Linux (.so), macOS

## API

```c
/* Initialization */
void vr_menu_init(VRMenu* menu);

/* Button Input */
void vr_menu_on_button_pressed(VRMenu* menu, VRButton button);
void vr_menu_on_button_released(VRMenu* menu, VRButton button);

/* Thumbstick Input */
void vr_menu_on_thumbstick(VRMenu* menu, float x, float y);

/* Update each frame */
void vr_menu_update(VRMenu* menu, float delta_time);

/* Menu Items */
int vr_menu_add_item(VRMenu* menu, int id, const char* label);\nvoid vr_menu_clear_items(VRMenu* menu);\nMenuItem* vr_menu_get_selected_item(VRMenu* menu);\nint vr_menu_get_item_count(VRMenu* menu);\n\n/* Callbacks */\nvoid vr_menu_set_select_callback(VRMenu* menu, void (*callback)(MenuItem* item));\nvoid vr_menu_set_back_callback(VRMenu* menu, void (*callback)(void));\n\n/* Position & Rotation */\nvoid vr_menu_set_position(VRMenu* menu, float x, float y, float z);\nvoid vr_menu_set_rotation(VRMenu* menu, float rx, float ry, float rz);\n\n/* State Queries */\nMenuState vr_menu_get_state(VRMenu* menu);\nfloat vr_menu_get_scale(VRMenu* menu);\nint vr_menu_is_visible(VRMenu* menu);\n```\n\n## Example Usage\n\n```cpp\n#include \"lib.h\"\n\nvoid on_select(MenuItem* item) {\n    printf(\"Selected: %s\\n\", item->label);\n}\n\nint main() {\n    VRMenu menu;\n    vr_menu_init(&menu);\n    \n    /* Add menu items */\n    vr_menu_add_item(&menu, 1, \"New Game\");\n    vr_menu_add_item(&menu, 2, \"Settings\");\n    vr_menu_add_item(&menu, 3, \"Quit\");\n    \n    /* Set position in front of player */\n    vr_menu_set_position(&menu, 0, 1.5f, -0.5f);\n    \n    /* Set callback */\n    vr_menu_set_select_callback(&menu, on_select);\n    \n    /* Main loop */\n    while (running) {\n        /* Get VR controller input */\n        if (controller.y_pressed) {\n            vr_menu_on_button_pressed(&menu, BUTTON_Y);\n        }\n        if (controller.y_released) {\n            vr_menu_on_button_released(&menu, BUTTON_Y);\n        }\n        if (controller.a_pressed) {\n            vr_menu_on_button_pressed(&menu, BUTTON_A);\n        }\n        if (controller.b_pressed) {\n            vr_menu_on_button_pressed(&menu, BUTTON_B);\n        }\n        \n        /* Thumbstick navigation */\n        vr_menu_on_thumbstick(&menu, controller.thumbstick_x, controller.thumbstick_y);\n        \n        /* Update menu */\n        vr_menu_update(&menu, delta_time);\n        \n        /* Render if visible */\n        if (vr_menu_is_visible(&menu)) {\n            float scale = vr_menu_get_scale(&menu);\n            \n            /* Render menu background at position with scale */\n            RenderMenuBackground(menu.x, menu.y, menu.z, scale);\n            \n            /* Render menu items */\n            for (int i = 0; i < vr_menu_get_item_count(&menu); i++) {\n                MenuItem* item = &menu.items[i];\n                int is_selected = (i == menu.selected_item);\n                RenderMenuItem(item->label, i, is_selected, scale);\n            }\n        }\n    }\n    \n    return 0;\n}\n```\n\n## Build\n\nBuilds automatically via GitHub Actions on every push:\n- Windows: `vrmenu.dll`\n- Linux: `libvrmenu.so`\n\nDownload from: [Actions](../../actions) tab\n\n## How It Works\n\n1. **Hold Y button** → Menu opens with smooth animation (scale 0→1)\n2. **Release Y button** → Menu closes with smooth animation\n3. **Use thumbstick** → Navigate menu items\n4. **Press A** → Select item (calls callback)\n5. **Press B** → Back/cancel\n\n## Integration\n\nThis library is engine-agnostic. Integrate it with:\n- Unity (call from C# via P/Invoke)\n- Unreal Engine (link as plugin)\n- OpenXR (wrap as XR interaction handler)\n- Custom VR engines\n