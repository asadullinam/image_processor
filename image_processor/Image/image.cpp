#include "image.h"

void Image::CheckHeightAndWidth(size_t height, size_t width) const {
    if (height <= 0 || width <= 0) {
        throw std::invalid_argument("Image dimensions must be positive.");
    }
}

Image::Image(size_t width, size_t height) : height_(height), width_(width) {
    CheckHeightAndWidth(height, width);
    pixel_colors_.resize(height);
    for (auto& row : pixel_colors_) {
        row.resize(width);
    }
}

Image::Image(const std::vector<std::vector<Color>>& data) {
    height_ = data.size();
    if (height_ > 0) {
        width_ = data[0].size();
    } else {
        width_ = 0;
    }
    CheckHeightAndWidth(height_, width_);
    pixel_colors_ = data;
}

Image::Image(const Image& image) : height_(image.height_), width_(image.width_), pixel_colors_(image.pixel_colors_) {
}

size_t Image::GetHeight() const {
    return height_;
}

size_t Image::GetWidth() const {
    return width_;
}

const std::vector<std::vector<Color>>& Image::GetData() const {
    return pixel_colors_;
}

Color& Image::GetColor(size_t x, size_t y) {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
    return pixel_colors_[x][y];
}

const Color& Image::GetColor(size_t x, size_t y) const {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
    return pixel_colors_[x][y];
}

void Image::SetColor(size_t x, size_t y, const Color& color) {
    if (x >= height_ || y >= width_) {
        throw std::out_of_range("Pixel coordinates out of range.");
    }
    pixel_colors_[x][y] = color;
}
