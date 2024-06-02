#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_UTILS_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_UTILS_H_

#include <iostream>
#include <string>
#include <vector>

namespace image::utils {
const int BMP_HEADER_SIZE = 14;
const int DIB_HEADER_SIZE = 40;
const int PADDING_SIZE = 4;
const int BYTES_PER_PIXEL = 3;
const int HEADER_WIDTH_OFFSET = 4;
const int HEADER_HEIGHT_OFFSET = 8;
const int FORMAT_FILE_FIRST_POSITION = 0;
const int FORMAT_FILE_SECOND_POSITION = 1;
const int SIZE_POSITION = 2;
const int PIXS_POSITION = 10;
const int DIB_HEADER_SIZE_POSITION = 0;
const int CNT_OF_PLANES = 1;
const int CNT_OF_PLANES_POSITION = 12;
const int BITS_PER_PIXEL = 24;
const int BITES_PER_PIXEL_POSITION = 14;
const int GAUSS_SIZE = 6;
const double GAUSS_COEF = 0.5;
const std::vector<char> FORMAT_BYTES = {'B', 'M'};
const std::vector<int> OFFSETS_OF_BYTES = {8, 16, 24};
const uint8_t MAX_COLOR_VALUE = 255;
const double GRAYSCALE_RED = 0.299;
const double GRAYSCALE_GREEN = 0.587;
const double GRAYSCALE_BLUE = 0.114;
const int BASIC_COLOR_1 = 255;
const int BASIC_COLOR_2 = 128;
const int BASIC_COLOR_3 = 64;
const int BASIC_WIDTH = 100;
const int BASIC_HEIGHT = 50;
const int BASIC_INCOR_1 = -10;
const int BASIC_INCOR_2 = -50;
};  // namespace image::utils

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_UTILS_H_
