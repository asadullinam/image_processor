
#ifndef CPP_HSE_TASKS_IMAGE_PROCESSOR_PARSER_PARSER_H_
#define CPP_HSE_TASKS_IMAGE_PROCESSOR_PARSER_PARSER_H_

#include <string>
#include <vector>

namespace parser {
struct Token {
    std::string name;
    std::vector<std::string> args;
    void Clear();
    bool Empty() const;
};

std::vector<Token> Parse(int argc, char** argv);
}  // namespace parser

#endif  // CPP_HSE_TASKS_IMAGE_PROCESSOR_PARSER_PARSER_H_
