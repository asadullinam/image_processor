#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_READER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_READER_H_

#include <cerrno>
#include <string>
#include "Utils.h"
#include "../Image/image.h"
#include <fstream>

namespace reading_and_writing {
class Reader {
public:
    explicit Reader(const std::string& path);
    Image Read();

private:
    std::string file_name_;
    size_t BytesToNumber(unsigned char* bytes) const;
};

const size_t GetPaddingSize(size_t width);
}  // namespace reading_and_writing

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_READER_AND_WRITER_READER_H_
