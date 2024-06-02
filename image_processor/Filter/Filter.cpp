#include "Filter.h"

template <typename T>
std::vector<T> filter::Filter::GetPixel(const std::vector<std::vector<T>>& matrix, const Image& img, std::size_t x,
                                        std::size_t y) const {
    T red = 0;
    T green = 0;
    T blue = 0;
    for (size_t i = 0; i < matrix.size(); ++i) {
        for (size_t j = 0; j < matrix.front().size(); ++j) {
            red += img.GetColor(std::clamp(static_cast<int>(i + x) - 1, static_cast<int>(0),
                                           static_cast<int>(img.GetHeight()) - 1),
                                std::clamp(static_cast<int>(j + y) - 1, static_cast<int>(0),
                                           static_cast<int>(img.GetWidth()) - 1))
                       .red *
                   matrix[i][j];
            green += img.GetColor(std::clamp(static_cast<int>(i + x) - 1, static_cast<int>(0),
                                             static_cast<int>(img.GetHeight()) - 1),
                                  std::clamp(static_cast<int>(j + y) - 1, static_cast<int>(0),
                                             static_cast<int>(img.GetWidth()) - 1))
                         .green *
                     matrix[i][j];
            blue += img.GetColor(std::clamp(static_cast<int>(i + x) - 1, static_cast<int>(0),
                                            static_cast<int>(img.GetHeight()) - 1),
                                 std::clamp(static_cast<int>(j + y) - 1, static_cast<int>(0),
                                            static_cast<int>(img.GetWidth()) - 1))
                        .blue *
                    matrix[i][j];
        }
    }
    return {blue, green, red};
}

uint8_t filter::Clamp(int color, const uint8_t max_color) {
    if (color < 0) {
        return 0;
    } else if (color > max_color) {
        return max_color;
    }
    return static_cast<uint8_t>(color);
}

Image filter::Crop::Apply(const Image& image) const {
    int new_width = std::min(width_, static_cast<int>(image.GetWidth()));
    int new_height = std::min(height_, static_cast<int>(image.GetHeight()));
    std::vector<std::vector<Color>> new_data;
    for (size_t i = image.GetHeight() - new_height; i < image.GetHeight(); ++i) {
        std::vector<Color> row;
        for (size_t j = 0; j < new_width; ++j) {
            row.push_back(image.GetColor(i, j));
        }
        new_data.push_back(row);
    }
    return Image{new_data};
}

Image filter::Grayscale::Apply(const Image& image) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        std::vector<Color> row(image.GetWidth());
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            const Color& pixel = image.GetColor(i, j);
            int grey = static_cast<int>(image::utils::GRAYSCALE_RED * static_cast<double>(pixel.red) +
                                        image::utils::GRAYSCALE_GREEN * static_cast<double>(pixel.green) +
                                        image::utils::GRAYSCALE_BLUE * static_cast<double>(pixel.blue));
            row[j] = {Clamp(grey), Clamp(grey), Clamp(grey)};
        }
        new_data.push_back(row);
    }
    return Image{new_data};
}

Image filter::Sharpening::Apply(const Image& image) const {
    std::vector<std::vector<Color>> new_data;
    const std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        std::vector<Color> row(image.GetWidth());
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            std::vector<int> colours = GetPixel(matrix, image, i, j);
            row[j].blue = Clamp(colours[0]);
            row[j].green = Clamp(colours[1]);
            row[j].red = Clamp(colours[2]);
        }
        new_data.push_back(row);
    }
    return Image{new_data};
}

Image filter::Negative::Apply(const Image& image) const {
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < image.GetHeight(); ++i) {
        std::vector<Color> row(image.GetWidth());
        for (size_t j = 0; j < image.GetWidth(); ++j) {
            row[j] = {static_cast<uint8_t>(image::utils::MAX_COLOR_VALUE - image.GetColor(i, j).red),
                      static_cast<uint8_t>(image::utils::MAX_COLOR_VALUE - image.GetColor(i, j).green),
                      static_cast<uint8_t>(image::utils::MAX_COLOR_VALUE - image.GetColor(i, j).blue)};
        }
        new_data.push_back(row);
    }
    return Image{new_data};
}

Image filter::EdgeDetection::Apply(const Image& image) const {
    Image ready_image = Grayscale().Apply(image);
    const std::vector<std::vector<int>> matrix = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    std::vector<std::vector<Color>> new_data;
    for (size_t i = 0; i < ready_image.GetHeight(); ++i) {
        std::vector<Color> row(ready_image.GetWidth());
        for (size_t j = 0; j < ready_image.GetWidth(); ++j) {
            std::vector<int> colours = GetPixel(matrix, ready_image, i, j);
            row[j].blue = Clamp(colours[0]);
            row[j].green = Clamp(colours[1]);
            row[j].red = Clamp(colours[2]);
            if (row[j].blue > threshold_ || row[j].red > threshold_ || row[j].green > threshold_) {
                row[j].blue = image::utils::MAX_COLOR_VALUE;
                row[j].green = image::utils::MAX_COLOR_VALUE;
                row[j].red = image::utils::MAX_COLOR_VALUE;
            } else {
                row[j].blue = 0;
                row[j].green = 0;
                row[j].red = 0;
            }
        }
        new_data.push_back(row);
    }
    return Image{new_data};
}

Image filter::GaussianBlur::Apply(const Image& image) const {
    std::vector<std::vector<Color>> new_data;
    int size = static_cast<int>(image::utils::GAUSS_SIZE * sigma_) + 1;
    std::vector<double> gauss_coef(size);
    double sum = 0.0;

    for (int i = 0; i < size; ++i) {
        gauss_coef[i] = exp(-image::utils::GAUSS_COEF * pow((i - size / 2) / sigma_, 2));
        sum += gauss_coef[i];
    }

    for (int i = 0; i < size; ++i) {
        gauss_coef[i] /= sum;
    }

    for (int y = 0; y < image.GetHeight(); ++y) {
        std::vector<Color> row(image.GetWidth());
        for (int x = 0; x < image.GetWidth(); ++x) {
            double red_sum = 0.0;
            double green_sum = 0.0;
            double blue_sum = 0.0;
            double weight_sum = 0.0;
            for (int i = 0; i < size; ++i) {
                int pixel_x = std::clamp(x + i - size / 2, 0, static_cast<int>(image.GetWidth() - 1));
                const Color& pixel_color = image.GetColor(y, pixel_x);
                double weight = gauss_coef[i];

                red_sum += pixel_color.red * weight;
                green_sum += pixel_color.green * weight;
                blue_sum += pixel_color.blue * weight;
                weight_sum += weight;
            }
            uint8_t red = Clamp(static_cast<int>(red_sum / weight_sum));
            uint8_t green = Clamp(static_cast<int>(green_sum / weight_sum));
            uint8_t blue = Clamp(static_cast<int>(blue_sum / weight_sum));
            row[x] = {red, green, blue};
        }
        new_data.push_back(row);
    }

    for (int x = 0; x < image.GetWidth(); ++x) {
        std::vector<double> red_sum(image.GetHeight(), 0.0);
        std::vector<double> green_sum(image.GetHeight(), 0.0);
        std::vector<double> blue_sum(image.GetHeight(), 0.0);
        std::vector<double> weight_sum(image.GetHeight(), 0.0);
        for (int y = 0; y < image.GetHeight(); ++y) {
            for (int i = 0; i < size; ++i) {
                int pixel_y = std::clamp(y + i - size / 2, 0, static_cast<int>(image.GetHeight() - 1));
                const Color& pixel_color = new_data[pixel_y][x];
                double weight = gauss_coef[i];
                red_sum[y] += pixel_color.red * weight;
                blue_sum[y] += pixel_color.blue * weight;
                green_sum[y] += pixel_color.green * weight;
                weight_sum[y] += weight;
            }
        }
        for (int y = 0; y < image.GetHeight(); ++y) {
            uint8_t red = Clamp(static_cast<int>(red_sum[y] / weight_sum[y]));
            uint8_t green = Clamp(static_cast<int>(green_sum[y] / weight_sum[y]));
            uint8_t blue = Clamp(static_cast<int>(blue_sum[y] / weight_sum[y]));
            new_data[y][x] = {red, green, blue};
        }
    }
    return Image{new_data};
}

Image filter::Mosaic::Apply(const Image& image) const {
    if (image.GetWidth() < block_size_ || image.GetWidth() < block_size_) {
        throw std::invalid_argument("Invalid block size for Mosaic filter");
    }
    const int new_width = static_cast<int>(image.GetWidth()) - (static_cast<int>(image.GetWidth()) % block_size_);
    const int new_height = static_cast<int>(image.GetHeight()) - (static_cast<int>(image.GetHeight()) % block_size_);
    Image ready_image = Crop(new_width, new_height).Apply(image);
    std::vector<std::vector<Color>> new_data;

    for (int i = 0; i < new_height; i += block_size_) {
        for (int j = 0; j < new_width; j += block_size_) {
            int64_t red = 0;
            int64_t green = 0;
            int64_t blue = 0;
            int pixel_count = 0;
            for (int x = i; x < i + block_size_; x++) {
                for (int y = j; y < j + block_size_; y++) {
                    red += ready_image.GetColor(x, y).red;
                    green += ready_image.GetColor(x, y).green;
                    blue += ready_image.GetColor(x, y).blue;
                    pixel_count++;
                }
            }
            if (pixel_count != 0) {
                red /= pixel_count;
                green /= pixel_count;
                blue /= pixel_count;
                Color start_value = {static_cast<uint8_t>(red), static_cast<uint8_t>(green),
                                     static_cast<uint8_t>(blue)};
                for (int x = i; x < i + block_size_; x++) {
                    for (int y = j; y < j + block_size_; y++) {
                        ready_image.SetColor(x, y, start_value);
                    }
                }
            }
        }
    }
    return {ready_image};
}

std::unique_ptr<filter::Filter> filter::CreateFilter(const parser::Token& token) {
    const std::string& filter = token.name;
    if (filter == "-sharp") {
        if (!token.args.empty()) {
            throw std::invalid_argument("Invalid argument for sharpening filter");
        }
        return std::make_unique<Sharpening>();
    } else if (filter == "-neg") {
        if (!token.args.empty()) {
            throw std::invalid_argument("Invalid argument for negative filter");
        }
        return std::make_unique<Negative>();
    } else if (filter == "-crop") {
        if (token.args.size() != 2) {
            throw std::invalid_argument("Invalid argument for crop filter");
        }
        try {
            int width = std::stoi(token.args[0]);
            int height = std::stoi(token.args[1]);
            if (width < 0 || height < 0) {
                throw std::invalid_argument("Non-positive value for crop filter");
            }
            return std::make_unique<Crop>(width, height);
        } catch (const std::invalid_argument& e) {
            throw std::invalid_argument("Invalid argument: " + std::string(e.what()));
        }

    } else if (filter == "-gs") {
        if (!token.args.empty()) {
            throw std::invalid_argument("Invalid argument for grayscale filter");
        }
        return std::make_unique<Grayscale>();
    } else if (filter == "-edge") {
        if (token.args.size() != 1) {
            throw std::invalid_argument("Invalid argument for edge detection filter");
        }
        double threshold = std::stod(token.args[0]);
        if (threshold < 0) {
            throw std::invalid_argument("Negative value for edge detection filter");
        } else if (threshold > 1) {
            throw std::invalid_argument("Too big value for edge detection filter");
        } else {
            threshold = threshold * image::utils::MAX_COLOR_VALUE;
            return std::make_unique<EdgeDetection>(static_cast<int>(threshold));
        }
    } else if (filter == "-blur") {
        if (token.args.size() != 1) {
            throw std::invalid_argument("Invalid argument for Gaussion blur filter");
        }
        double sigma = std::stod(token.args[0]);
        return std::make_unique<GaussianBlur>(sigma);
    } else if (filter == "-mos") {
        if (token.args.size() != 1) {
            throw std::invalid_argument("Invalid argument for Mosaic filter");
        }
        int block_size = std::stoi(token.args[0]);
        if (block_size <= 0) {
            throw std::invalid_argument("Non-positive value for Mosaic filter");
        }
        return std::make_unique<Mosaic>(block_size);
    } else {
        throw std::invalid_argument("Invalid filter" + filter);
    }
}
