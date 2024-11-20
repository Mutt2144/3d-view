#ifndef GWM_TEXTURE_HPP
#define GWM_TEXTURE_HPP

#include <iostream>

#include <SDL2/SDL_image.h>
#include <GL/gl.h>

class TEXTURES {
public:
    GLuint load_texture(const char* filename);
};

#endif // GWM_TEXTURE_HPP