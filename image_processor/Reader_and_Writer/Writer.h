#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_WRITER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_WRITER_H_

#include "../Image/image.h"
#include <utility>
#include <string>
#include "Utils.h"
#include <fstream>
#include <cerrno>
#include "Reader.h"
#include <algorithm>

namespace reading_and_writing {
class Writer {
public:
    explicit Writer(std::string path);
    void Write(const Image& image);

private:
    void WriteBMPHeader(unsigned char* bmp_header, size_t size_of_title);
    void WriteDIBHeader(unsigned char* dib_header, size_t width, size_t height);

    template <typename T>
    void NumberToBytes(T number, unsigned char* bytes);

    std::string filename_;
};
}  // namespace reading_and_writing

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_WRITER_H_
