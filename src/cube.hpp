#ifndef CUBE_HPP
#define CUBE_HPP

#include <iostream>
#include <GL/gl.h>

struct VECTOR2D {
    float x, y;
};

enum BLOCKS_TYPE {
    AIR,
    GRASS,
    DIRT,
    STONE
};

struct CUBE {
    float x, y, z;
    short type;
    bool selected;
};

struct LAYER {
    CUBE cubes[16][16];
};

struct CHUNK {
    LAYER layers[64];
    float chunkX, chunkZ;
};

void draw_cube(CUBE cube, GLuint textureSide, GLuint textureTop, GLuint textureBottom, bool drawFace[6], bool selected, VECTOR2D chunkPos) {
    glBindTexture(GL_TEXTURE_2D, textureSide);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);

    if (selected) glColor4f(.5f, .5f, .5f, 1.0f);
    
    if (drawFace[3]) {
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 0);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 1);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(0, 1);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2) + (chunkPos.y * 16));
        glEnd();
    }

    // left face
    if (drawFace[1]) {
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y  * 2+ 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 0);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y  * 2+ 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 1);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y  * 2- 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(0, 1);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y  * 2- 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
        glEnd();
    }

    // right face
    if (drawFace[2]) {
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 0);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 1);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(0, 1);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2) + (chunkPos.y * 16));
        glEnd();
    }

    // back face
    if (drawFace[0]) {
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 0);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 1);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(0, 1);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
        glEnd();
    }

    // top face
    if (drawFace[4]) {
        glBindTexture(GL_TEXTURE_2D, textureTop);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 0);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 1);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(0, 1);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 + 1, (cube.z * 2) + (chunkPos.y * 16));
        glEnd();
    }

    // bottom face
    if (drawFace[5]) {
        glBindTexture(GL_TEXTURE_2D, textureBottom);
        glBegin(GL_QUADS);
            glTexCoord2f(0, 0);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 0);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2 - 2) + (chunkPos.y * 16));
            glTexCoord2f(1, 1);         glVertex3f((cube.x * 2 + 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2) + (chunkPos.y * 16));
            glTexCoord2f(0, 1);         glVertex3f((cube.x * 2 - 1) + (chunkPos.x * 16), cube.y * 2 - 1, (cube.z * 2) + (chunkPos.y * 16));
        glEnd();
    }

    glColor4f(1, 1, 1, 1);
    glDisable(GL_TEXTURE_2D);
}

#endif