#pragma once
#include <bit>
#include <bitset>
#include <vector>
#include "quads.h"

#ifndef GREEDY_MESHING_TERRAIN_H
#define GREEDY_MESHING_TERRAIN_H

bool worldMap[32][32][32];

void initMap() {
    for (auto & x : worldMap) {
        for (auto & y : x) {
            for (auto & z : y) {
                z = false;
            }
        }
    }
}

void addBlock(int x, int y, int z) {
    worldMap[x][y][z] = true;
}

uint toMask(int h) {
    std::bitset<32> mask;
    for (int i = 0; i < h; i++) {
        mask.set(i);
    }
    return mask.to_ulong();
}

void greedy_mesh(uint data[32], std::vector<quad> &quads, int z, int direction) {
    for (int x = 0; x < 32; x++) {
        int y = 0;
        while (y < 32) {
            y += std::__countr_zero(data[x] >> y);
            if (y >= 32) {
                break;
            }
            int h = std::__countr_one(data[x] >> y);
            uint mask = toMask(h) << y;
            int w = 1;
            while (w + x < 32) {
                uint nextRow = data[x+w] & mask;
                if (nextRow != mask) {
                    break;
                }
                data[x+w] = data[x+w] & (~mask);
                w++;
            }
            quads.push_back(quad(
                x,
                y,
                z,
                w,
                h,
                direction
            ));
            y += h;
        }
    }
}

std::vector<quad> meshVolume() {
    std::vector<quad> quads;
    uint data[32];
    for (int z = 0; z < 32; z++) {
        for (int x = 0; x < 32; x++) {
            std::bitset<32> number;
            for (int y = 0; y < 32; y++) {
                number.set(y, worldMap[x][y][z]);
            }
            data[x] = number.to_ulong();
        }
        greedy_mesh(data, quads, z, 0);
    }
}

#endif //GREEDY_MESHING_TERRAIN_H
