//
// Created by yan on 2026-09-06.
//
#pragma once
#include <iostream>

#ifndef MYAPP_QUADS_H
#define MYAPP_QUADS_H


struct quad {
    __uint32_t allPoints;

    quad(__uint32_t allPoints) : allPoints(allPoints) {}
    quad(__uint8_t x, __uint8_t y, __uint8_t z, __uint8_t w, __uint8_t h, __uint8_t dir) {
        allPoints = dir << 25 | h << 20 | w << 15 | z << 10 | y << 5 | x;
    }

    uint x();
    uint y();
    uint z();
    uint w();
    uint h();
    uint dir();
};


#endif //MYAPP_QUADS_H
