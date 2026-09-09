//
// Created by yan on 2026-09-06.
//

#include "quads.h"

uint quad::x() {
    return allPoints & 31;
}
uint quad::y() {
    return allPoints >> 5 & 31;
}
uint quad::z() {
    return allPoints >> 10 & 31;
}
uint quad::w() {
    return allPoints >> 15 & 31;
}
uint quad::h() {
    return allPoints >> 20 & 31;
}
uint quad::dir() {
    return allPoints >> 25 & 7;
}