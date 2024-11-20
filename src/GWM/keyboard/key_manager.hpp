#ifndef GWM_KEYS_HPP
#define GWM_KEYS_HPP
// Not used yet

class KEYS {
public:
    unsigned char keys[256];
    unsigned char special_keys[256];

    void handle_keyboard(unsigned char key, int x, int y);
    void handle_keyboard_up(unsigned char key, int x, int y);

    void handle_special_keys(int key, int x, int y);
    void handle_special_keys_up(int key, int x, int y);
};



#endif