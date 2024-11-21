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
    
    // clear the chunk
    for (int y = 0; y < 64; y++) {
        for (int x = 0; x < 16; x++) {
            for (int z = 0; z < 16; z++) {
                chunk->layers[y].cubes[x][z].type = AIR;
            }
        }
    }

    // create noise map
    for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {
            map[x][z] = a + rand() / (RAND_MAX / (b - t));
            //map[x][z]
        }
    }

    // make the noise map smoother
    for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {
            if (x > 0) {
                if (map[x - 1][z] > map[x][z]) {
                    float difference = map[x - 1][z] - map[x][z];
                    map[x][z] += difference / 1.5;
                }
            }
            if (x < 15) {
                if (map[x + 1][z] > map[x][z]) {
                    float difference = map[x + 1][z] - map[x][z];
                    map[x][z] += difference / 1.5;
                }
            }

            if (z > 0) {
                if (map[x][z -1] > map[x][z]) {
                    float difference = map[x][z - 1] - map[x][z];
                    map[x][z] += difference / 1.5;
                }
            }
            if (z < 15) {
                if (map[x][z + 1] > map[x][z]) {
                    float difference = map[x][z + 1] - map[x][z];
                    map[x][z] += difference / 1.5;
                }
            }
            
        }
    }

    for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {
            // create stone
            for (int y = 0; y < map[x][z] - 10; y++) {
                auto& cube = chunk->layers[y].cubes[x][z];
                cube.type = STONE;
            }

            // create dirt
            for (int y = map[x][z] - 10; y < map[x][z]; y++) {
                auto& cube = chunk->layers[y].cubes[x][z];
                cube.type = DIRT;
            }

            int y = static_cast<int>(map[x][z]);
            chunk->layers[y].cubes[x][z].type = GRASS;
        }
    }

    /*for (int x = 0; x < height; x++) {
        for (int z = 0; z < width; z++) {
            for (int y = map[x][z] + 1; y < 64; y++) {
                auto& cube = chunk->layers[y].cubes[x][z];
                cube.type = AIR;
            }
            
            int y = static_cast<int>(map[x][z]);

            chunk->layers[y].cubes[x][z].type = GRASS;

            for (int i = y; i > 0; i--) {
                auto& cube = chunk->layers[i].cubes[x][z];
                if (cube.type == GRASS) chunk->layers[i].cubes[x][z].type = DIRT;
            }
            //chunk->layers[(int)map[x][z]].cubes[x][z].type = GRASS;
        }
    }*/
}