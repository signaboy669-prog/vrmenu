#include <iostream>
#include "lib.h"

/* Callback for when user selects a menu item */
void on_item_selected(MenuItem* item) {
    if (item) {
        std::cout << "  [SELECTED] Item: " << item->label << " (ID: " << item->id << ")" << std::endl;
    }
}

/* Callback for when user presses back */
void on_back_pressed() {
    std::cout << "  [BACK] Menu back button pressed" << std::endl;
}

int main() {
    std::cout << "=== VR Menu Template - Full Demo ===\n" << std::endl;
    
    VRMenu menu;
    vr_menu_init(&menu);
    
    /* Set callbacks */
    vr_menu_set_select_callback(&menu, on_item_selected);
    vr_menu_set_back_callback(&menu, on_back_pressed);
    
    /* Add menu items */
    std::cout << "Adding menu items..." << std::endl;
    vr_menu_add_item(&menu, 1, "New Game");
    vr_menu_add_item(&menu, 2, "Load Game");
    vr_menu_add_item(&menu, 3, "Settings");
    vr_menu_add_item(&menu, 4, "About");
    std::cout << "Added " << vr_menu_get_item_count(&menu) << " items\n" << std::endl;
    
    /* Menu position and rotation */
    vr_menu_set_position(&menu, 0.0f, 1.5f, -0.5f);  /* 1.5m high, 0.5m in front */
    vr_menu_set_rotation(&menu, 0.0f, 0.0f, 0.0f);
    
    std::cout << "Menu initialized at (" << menu.x << ", " << menu.y << ", " << menu.z << ")" << std::endl;
    std::cout << "Initial state: " << vr_menu_get_state(&menu) << " (0=closed)\n" << std::endl;
    
    /* === DEMO: Y-button hold sequence === */
    std::cout << "\n[DEMO] Pressing Y button to open menu..." << std::endl;
    vr_menu_on_button_pressed(&menu, BUTTON_Y);
    
    /* Simulate opening animation */
    for (int i = 0; i <= 5; i++) {
        vr_menu_update(&menu, 0.1f);
        std::cout << "  Frame " << i << ": State=" << vr_menu_get_state(&menu) 
                  << " Scale=" << vr_menu_get_scale(&menu) << std::endl;
    }
    
    /* Menu is now open, simulate navigation */
    std::cout << "\n[DEMO] Menu open. Navigating with thumbstick..." << std::endl;
    std::cout << "  Selected: " << vr_menu_get_selected_item(&menu)->label << std::endl;
    
    vr_menu_on_thumbstick(&menu, 0.0f, -0.7f);  /* Move down */
    std::cout << "  Selected: " << vr_menu_get_selected_item(&menu)->label << std::endl;
    
    vr_menu_on_thumbstick(&menu, 0.0f, -0.7f);  /* Move down again */
    std::cout << "  Selected: " << vr_menu_get_selected_item(&menu)->label << std::endl;
    
    /* Simulate A-button press (select) */
    std::cout << "\n[DEMO] Pressing A button to select..." << std::endl;
    vr_menu_on_button_pressed(&menu, BUTTON_A);
    
    /* Simulate B-button press (back) */
    std::cout << "\n[DEMO] Pressing B button for back..." << std::endl;
    vr_menu_on_button_pressed(&menu, BUTTON_B);
    
    /* Simulate closing animation */
    std::cout << "\n[DEMO] Closing animation..." << std::endl;
    for (int i = 0; i <= 4; i++) {
        vr_menu_update(&menu, 0.1f);
        std::cout << "  Frame " << (5 + i) << ": State=" << vr_menu_get_state(&menu) 
                  << " Scale=" << vr_menu_get_scale(&menu) << std::endl;
    }
    
    std::cout << "\nMenu visible: " << vr_menu_is_visible(&menu) << std::endl;
    std::cout << "\n=== Demo Complete ===" << std::endl;
    return 0;
}
