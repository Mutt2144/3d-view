#include "texture.hpp"

GLuint TEXTURES::load_texture(const char* filename) {
    SDL_Surface* surface = IMG_Load(filename);
    if (!surface) {
        std::cerr << "Failed to load image: " << filename << "\n";
        return 0;
    }

    // invete a imagem verticalmente
    /*SDL_LockSurface(surface);
    Uint8* pixels = static_cast<Uint8*>(surface->pixels);
    Uint8* temp = new Uint8[surface->pitch];
    for (int y = 0; y < surface->h / 2; ++y) {
        memcpy(temp, pixels + y * surface->pitch, surface->pitch);
        memcpy(pixels + y * surface->pitch, pixels + (surface->h - 1 - y) * surface->pitch, surface->pitch);
        memcpy(pixels + (surface->h - 1 - y) * surface->pitch, temp, surface->pitch);
    }

    delete[] temp;*/
    SDL_UnlockSurface(surface);
    

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    // habilita blending para transparencia
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    GLenum format = (surface->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, surface->w, surface->h, 0, format, GL_UNSIGNED_BYTE, surface->pixels);

    SDL_FreeSurface(surface);

    return textureID;
}