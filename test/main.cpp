#include <iostream>
#include "lib.h"

int main() {
    std::cout << "=== VR Menu Template Demo ===" << std::endl;
    
    VRMenu menu;
    vr_menu_init(&menu);
    
    std::cout << "Menu initialized at (0, 0, -0.5)" << std::endl;
    std::cout << "Initial state: " << vr_menu_get_state(&menu) << std::endl;
    std::cout << "Initial scale: " << vr_menu_get_scale(&menu) << std::endl;
    
    /* Simulate Y button press and hold */
    std::cout << "\n[Simulating Y button press...]" << std::endl;
    vr_menu_on_button_pressed(&menu, BUTTON_Y);
    
    /* Simulate opening animation over 0.5 seconds */
    for (int i = 0; i <= 5; i++) {
        vr_menu_update(&menu, 0.1f);
        std::cout << "  t=" << (i * 0.1f) << "s - State: " << vr_menu_get_state(&menu) 
                  << " Scale: " << vr_menu_get_scale(&menu) << std::endl;
    }
    
    /* Simulate Y button release */
    std::cout << "\n[Simulating Y button release...]" << std::endl;
    vr_menu_on_button_released(&menu, BUTTON_Y);
    
    /* Simulate closing animation */
    for (int i = 0; i <= 4; i++) {
        vr_menu_update(&menu, 0.1f);
        std::cout << "  t=" << ((5 + i) * 0.1f) << "s - State: " << vr_menu_get_state(&menu) 
                  << " Scale: " << vr_menu_get_scale(&menu) << std::endl;
    }
    
    std::cout << "\nMenu is visible: " << vr_menu_is_visible(&menu) << std::endl;
    std::cout << "\nDemo complete!" << std::endl;
    return 0;
}
