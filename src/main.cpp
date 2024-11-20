#include <iostream>
#include <vector>

#include <math.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "GWM/gwm.hpp"

#include "cube.hpp"
#include "perlin.cpp"

GWM Gwm;

LAYER layer1;

CHUNK chunk1;

std::vector<std::vector<CHUNK>> chunks = {
    {CHUNK(), CHUNK()},
    {CHUNK(), CHUNK()}
};

float playerChunk[2] = { 0, 0 };
VECTOR2D mousePos;

GLuint grass_top;
GLuint grass_side;
GLuint grass_bottom;

GLuint dirt_top_side_bottom;

GLuint stone_top_side_bottom;

unsigned char keys[256];
int special_keys[256];

GWM_CAMERA camera;

void create_layer() {
    for (int x = 0; x < 16; x++) {
        for (int z = 0; z < 16; z++) {
            layer1.cubes[x][z].x = x;
            layer1.cubes[x][z].y = 0;
            layer1.cubes[x][z].z = z;
            layer1.cubes[x][z].type = GRASS;
        }
    }
}

void create_chunk() {
    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                short type;

                if (y > 15) type = AIR;
                else if (y == 15) type = GRASS;
                else if (y <= 14 && y > 5) type = DIRT;
                else type = STONE;

                chunk1.layers[y].cubes[x][z] = { (float)x, (float)y, (float)z, type };
            }
        }
    }

    for (int chunkX = 0; chunkX < chunks.size(); chunkX++) {
        for (int chunkZ = 0; chunkZ < chunks[chunkX].size(); chunkZ++) {
            
            for (int y = 0; y < 64; y++) {
                for (int x = 0; x < 16; x++) {
                    for (int z = 0; z < 16; z++) {
                        chunks[chunkX][chunkZ].layers[y].cubes[x][z] = chunk1.layers[y].cubes[x][z];
                    }
                }
            }
        }
    }

    //chunk1.layers[0].cubes[0][0].selected = true;

    for (int x = 0; x < chunks.size(); x++) {
        for (int z = 0; z < chunks[x].size(); z++) {
            chunks[x][z].chunkX = x;
            chunks[x][z].chunkZ = z;
        }
    }
}

void idle() {
    glutPostRedisplay();
}

#pragma region Camera Functions

void update_camera_rotation() {
    float yawRadians = camera.yaw * M_PI / 180.0f;
    float pitchRadians = camera.pitch * M_PI / 180.0f;

    camera.eyeX =  cos(pitchRadians) * sin(yawRadians);
    camera.eyeY =  sin(pitchRadians);
    camera.eyeZ = -cos(pitchRadians) * cos(yawRadians);
}

void move_camera() {
    float yawRadians = camera.yaw * M_PI / 180.0f;

    if (yawRadians != 0) yawRadians = -yawRadians;

    float speed = 0.2f;

    if (keys['w']) {
        camera.x -= sin(yawRadians) * speed;
        camera.z -= cos(yawRadians) * speed;
    }
    if (keys['s']) {
        camera.x += sin(yawRadians) * speed;
        camera.z += cos(yawRadians) * speed;
    }

    if (keys['a']) {
        camera.x -= cos(yawRadians) * speed;
        camera.z += sin(yawRadians) * speed;
    }
    if (keys['d']) {
        camera.x += cos(yawRadians) * speed;
        camera.z -= sin(yawRadians) * speed;
    }

    if (keys[' ']) {
        camera.y += speed;
    }

    if (keys['c']) {
        camera.y -= speed;
    }
}

void handle_mouse_movement(int x, int y) {
    VECTOR2D newPos = VECTOR2D{(float)x, (float)y};

    VECTOR2D delta = { newPos.x - mousePos.x, newPos.y - mousePos.y };

    float sensitivity = 0.1f; // ou o valor que funcionar melhor
    camera.yaw += delta.x * sensitivity;
    camera.pitch += -delta.y * sensitivity;

    mousePos = newPos;
    std::cout << camera.yaw << " " << camera.pitch << std::endl;
}

#pragma endregion

#pragma region Keyboard
void handle_keyboard(unsigned char key, int x, int y) {
    /*if (key == 'w') camera.z += 0.01f;
    else std::cout  << "key: " << key << std::endl;*/
    keys[key] = 1;
}
void handle_keyboard_up(unsigned char key, int x, int y) {
    keys[key] = 0;
}


void handle_special_keys(int key, int x, int y) {
    special_keys[key] = 1;
    
    if (key == GLUT_KEY_F1) {
        exit(0);
    }
}
void handle_special_keys_up(int key, int x, int y) {
    special_keys[key] = 0;
}
#pragma endregion

void draw_chunks() {
    for (float chunkX = 0; chunkX < chunks.size(); chunkX++) {
        for (float chunckZ = 0; chunckZ < chunks[chunkX].size(); chunckZ++) {
            for (int y = 0; y < 64; y++) {
                for (int x = 0; x < 16; x++) {
                    for (int z = 0; z < 16; z++) {
                        VECTOR2D chunckPos = { chunkX, chunckZ };

                        GLuint textureSide   = 0;
                        GLuint textureTop    = 0;
                        GLuint textureBottom = 0;

                        if (chunks[chunkX][chunckZ].layers[y].cubes[x][z].type == GRASS) {
                            textureSide = grass_side;
                            textureTop = grass_top;
                            textureBottom = grass_bottom;
                        }
                        else if (chunks[chunkX][chunckZ].layers[y].cubes[x][z].type == DIRT) {
                            textureSide = dirt_top_side_bottom;
                            textureTop = dirt_top_side_bottom;
                            textureBottom = dirt_top_side_bottom;
                        }
                        else if (chunks[chunkX][chunckZ].layers[y].cubes[x][z].type == STONE) {
                            textureSide = stone_top_side_bottom;
                            textureTop = stone_top_side_bottom;
                            textureBottom = stone_top_side_bottom;
                        }


                        if (chunks[chunkX][chunckZ].layers[y].cubes[x][z].type != AIR) {
                            // esta sessao verifica se tem algum bloco do lado, se tiver não desenha a face ao lado

                            bool drawFace[6] = { true, true, true, true, true, true };

                            // cima                
                            if (y >= 63) drawFace[4] = true;
                            else if (chunks[chunkX][chunckZ].layers[y + 1].cubes[x][z].type != AIR) drawFace[4] = false;

                            // baixo
                            if (y <= 0) drawFace[5] = true;
                            else if (y <= 63)
                                if (chunks[chunkX][chunckZ].layers[y - 1].cubes[x][z].type != AIR) drawFace[5] = false;

                            // esquerda
                            if (x <= 0) drawFace[1] = true;
                            else if (chunks[chunkX][chunckZ].layers[y].cubes[x - 1][z].type != AIR) drawFace[1] = false;

                            // direita
                            if (x >= 15) drawFace[2] = true;
                            else if (chunks[chunkX][chunckZ].layers[y].cubes[x + 1][z].type != AIR) drawFace[2] = false;

                            // frente
                            if (z <= 0) drawFace[0] = true;
                            else if (chunks[chunkX][chunckZ].layers[y].cubes[x][z - 1].type != AIR) drawFace[0] = false;

                            // tras
                            if (z >= 15) drawFace[3] = true;
                            else if (chunks[chunkX][chunckZ].layers[y].cubes[x][z + 1].type != AIR) drawFace[3] = false;

                            draw_cube(chunks[chunkX][chunckZ].layers[y].cubes[x][z], textureSide, textureTop, textureBottom, drawFace, chunk1.layers[y].cubes[x][z].selected, chunckPos);
                        }
                    }
                }
            }
        }
    }
}

void display() {
    #pragma region Camera Logic
    move_camera();

    if (special_keys[GLUT_KEY_UP])    camera.pitch += 1.0f;
    if (special_keys[GLUT_KEY_DOWN])  camera.pitch -= 1.0f;
    if (special_keys[GLUT_KEY_LEFT])  camera.yaw   -= 1.0f;
    if (special_keys[GLUT_KEY_RIGHT]) camera.yaw   += 1.0f;

    if (camera.pitch > 89.0f) camera.pitch = 89.0f;
    if (camera.pitch < -89.0f) camera.pitch = -89.0f;

    update_camera_rotation();

    playerChunk[0] = (camera.x / 16 / 2);
    playerChunk[1] = (camera.z / 16 / 2);

    if (playerChunk[0] < 0) playerChunk[0] = (int)playerChunk[0] - 1;
    else playerChunk[0] = (int)playerChunk[0];

    if (playerChunk[1] < 0) playerChunk[1] = (int)playerChunk[1] - 1;
    else playerChunk[1] = (int)playerChunk[1];

    //std::cout << "Player chunck: " << playerChunk[0] << ", " << playerChunk[1] << std::endl;
    #pragma endregion

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();
    //glTranslatef(camera.x, camera.y, camera.z);
    gluLookAt(camera.x, camera.y, camera.z,
              camera.x + camera.eyeX, camera.y + camera.eyeY, camera.z + camera.eyeZ,
              0.0f, 1.0f, 0.0f);

    draw_chunks();

    glutSwapBuffers();
}

int main(int argc, char** argv) {
    #pragma region Init / Config

    camera.x = 0.0f;
    camera.y = 0.0f;
    camera.z = 0.0f;

    Gwm.init(&argc, argv, 840, 680, "Minecraft Clone");

    grass_top = Gwm.Textures.load_texture("assets/grass-top.png");
    grass_side = Gwm.Textures.load_texture("assets/grass-side.png");
    grass_bottom = Gwm.Textures.load_texture("assets/grass-bottom.png");

    dirt_top_side_bottom = Gwm.Textures.load_texture("assets/grass-bottom.png");

    stone_top_side_bottom = Gwm.Textures.load_texture("assets/stone.png");

    create_layer();
    create_chunk();

    generate_noise_map(16, 16, &chunks[0][0], 15.0f, 7.0f, 10.0f);
    generate_noise_map(16, 16, &chunks[1][0], 15.0f, 7.0f, 10.0f);
    generate_noise_map(16, 16, &chunks[0][1], 15.0f, 7.0f, 10.0f);
    generate_noise_map(16, 16, &chunks[1][1], 15.0f, 7.0f, 10.0f);

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutMainLoop();

    #pragma endregion
    return 0;
}