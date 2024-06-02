#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_COLOR_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_COLOR_H_

#include <cstdint>
#include <stdexcept>
#include "../Reader_and_Writer/Utils.h"

struct Color {
    Color() = default;
    Color(uint8_t red, uint8_t green, uint8_t blue);
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;

    void SetColors(uint8_t red, uint8_t green, uint8_t blue);
};

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_COLOR_H_
