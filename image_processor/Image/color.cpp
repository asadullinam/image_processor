#include "color.h"

Color::Color(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {
}

void Color::SetColors(uint8_t new_red, uint8_t new_green, uint8_t new_blue) {
    if (new_red > image::utils::MAX_COLOR_VALUE || new_green > image::utils::MAX_COLOR_VALUE ||
        new_blue > image::utils::MAX_COLOR_VALUE) {
        throw std::out_of_range("Color component values must be in the range [0, 255]");
    }
    red = new_red;
    green = new_green;
    blue = new_blue;
}