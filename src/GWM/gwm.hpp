#ifndef GWM_MAIN_HPP
#define GWM_MAIN_HPP

#include <iostream>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "texture/texture.hpp"
#include "keyboard/key_manager.hpp"

void handle_keyboard(unsigned char key, int x, int y);
void handle_keyboard_up(unsigned char key, int x, int y);
void handle_special_keys(int key, int x, int y);
void handle_special_keys_up(int key, int x, int y);

void handle_mouse_movement(int x, int y);

class GWM_CAMERA {
public:
    float x, y, z;
    float yaw, pitch;
    float eyeX, eyeY, eyeZ;
    float speedX, speedY;
};

class GWM {
public:
    void init(int *pargc, char **argv, int w, int h, const char* title);

    TEXTURES Textures;
    KEYS Keys;
};

#endif // GWM_MAIN_HPP