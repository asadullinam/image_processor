#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTER_FILTER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTER_FILTER_H_

#include <memory>
#include <algorithm>
#include <stdexcept>
#include <cmath>

#include "../Image/image.h"
#include "../Parser/Parser.h"
#include "../Reader_and_Writer/Utils.h"

namespace filter {
class Filter {
public:
    Filter() = default;
    virtual ~Filter() = default;
    virtual Image Apply(const Image& image) const = 0;

protected:
    template <typename T>
    std::vector<T> GetPixel(const std::vector<std::vector<T>>& matrix, const Image& img, std::size_t x,
                            std::size_t y) const;
};

class Sharpening : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class Negative : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class Crop : public Filter {
public:
    Crop(int width, int height) : width_(width), height_(height) {
    }
    Image Apply(const Image& image) const override;

private:
    int width_;
    int height_;
};

class Grayscale : public Filter {
public:
    Image Apply(const Image& image) const override;
};

class EdgeDetection : public Filter {
public:
    explicit EdgeDetection(int threshold) : threshold_(threshold) {
    }
    Image Apply(const Image& image) const override;

private:
    double threshold_;
};

class GaussianBlur : public Filter {
public:
    explicit GaussianBlur(double sigma) : sigma_(sigma) {
    }
    Image Apply(const Image& image) const override;

private:
    double sigma_;
};

class Mosaic : public Filter {
public:
    explicit Mosaic(int block_size) : block_size_(block_size) {
    }
    Image Apply(const Image& image) const override;

private:
    int block_size_;
};

std::unique_ptr<Filter> CreateFilter(const parser::Token& token);

uint8_t Clamp(int color, const uint8_t max_color = 255);

}  // namespace filter

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_FILTER_FILTER_H_
