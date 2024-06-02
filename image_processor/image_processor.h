#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_PROCESSOR_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_PROCESSOR_H_

#include <iostream>
#include <sstream>

#include "Filter/Filter.h"
#include "Image/image.h"
#include "Parser/Parser.h"
#include "Reader_and_Writer/Reader.h"
#include "Reader_and_Writer/Writer.h"

Image GetImage(const std::string& path);

std::vector<parser::Token> Parse(int argc, char** argv);

void WriteImage(const Image& image, const std::string& path);

Image ApplyFilter(Image& image, const std::vector<parser::Token>& tokens);

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_IMAGE_PROCESSOR_H_
