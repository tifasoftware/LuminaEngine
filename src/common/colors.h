#pragma once

struct Color {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;

    Color() {
        r = 0;
        g = 0;
        b = 0;
    }

    Color(uint8_t r, uint8_t g, uint8_t b) {
        this->r = r;
        this->g = g;
        this->b = b;
    }

    bool operator==(const Color& c) const {
        if (c.r == r && c.g == g && c.b == b) return true;
        return false;
    }

    bool operator!=(const Color& c) const {
        if (c.r != r || c.g != g || c.b != b) return true;
        return false;
    }
};

struct ColorA {
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t a = 0;

    ColorA() {
        r = 0;
        g = 0;
        b = 0;
        a = 0;
    }

    ColorA(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
        this->r = r;
        this->g = g;
        this->b = b;
        this->a = a;
    }

    bool operator==(const ColorA& c) const {
        if (c.r == r && c.g == g && c.b == b && c.a == a) return true;
        return false;
    }

    bool operator!=(const ColorA& c) const {
        if (c.r != r || c.g != g || c.b != b || c.a != a) return true;
        return false;
    }
};