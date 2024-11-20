#include "key_manager.hpp"

// keys
void KEYS::handle_keyboard(unsigned char key, int x, int y) {
    /*if (key == 'w') camera.z += 0.01f;
    else std::cout  << "key: " << key << std::endl;*/
    keys[key] = 1;
}

void KEYS::handle_keyboard_up(unsigned char key, int x, int y) {
    keys[key] = 0;
}


void KEYS::handle_special_keys(int key, int x, int y) {
    special_keys[key] = 1;
}

void KEYS::handle_special_keys_up(int key, int x, int y) {
    special_keys[key] = 0;
}