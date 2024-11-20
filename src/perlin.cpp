#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>

#include "cube.hpp"

void set_rand() {
    auto time = std::chrono::high_resolution_clock::now();

    int seed =  static_cast<int>(time.time_since_epoch().count());

    std::srand(seed);
}

void generate_noise_map(int width, int height, CHUNK* chunk, float a, float b, float t) {
    float map[width][height];
    set_rand();
    //std::srand(static_cast<unsigned>(std::time(nullptr)));

    for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {

            map[x][z] = a + rand() / (RAND_MAX / (b - t));

            for (int y = map[x][z]; y < 64; y++) {
                chunk->layers[y].cubes[x][z].type = AIR;
            }
            
            chunk->layers[(int)map[x][z]].cubes[x][z].type = GRASS;
        }
    }
}