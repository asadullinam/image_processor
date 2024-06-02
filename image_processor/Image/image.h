#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_IMAGE_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_IMAGE_H_

#include <cstdint>
#include <vector>
#include "color.h"

class Image {
private:
    size_t height_ = 0;
    size_t width_ = 0;
    std::vector<std::vector<Color>> pixel_colors_;
    void CheckHeightAndWidth(size_t height, size_t width) const;

public:
    Image() = default;
    Image(size_t width, size_t height);
    explicit Image(const std::vector<std::vector<Color>>& data);
    Image(const Image& image);
    ~Image() = default;

    size_t GetHeight() const;
    size_t GetWidth() const;
    const std::vector<std::vector<Color>>& GetData() const;
    Color& GetColor(size_t x, size_t y);
    const Color& GetColor(size_t x, size_t y) const;
    void SetColor(size_t x, size_t y, const Color& color);
};

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_IMAGE_H_
