#include "../../../../contrib/catch/catch.hpp"
#include "../../Image/image.h"
#include "../../Reader_and_Writer/Reader.h"
#include "../../Reader_and_Writer/Utils.h"
#include "../../Reader_and_Writer/Writer.h"
#include "../../Parser/Parser.h"
#include "../../image_processor.h"
#include "../../Filter/Filter.h"
#include "image_processor.h"
#include <filesystem>
#include <string>

TEST_CASE("Parser_test") {
    const char* argv[] = {
        "./image_processor", "input.bmp", "/tmp/output.bmp", "-crop", "800", "600", "-gs", "-blur", "0.5"};
    int argc = sizeof(argv) / sizeof(argv[0]);
    std::vector<parser::Token> tokens;
    std::vector<char*> argv_cstr;
    for (const auto& arg : argv) {
        argv_cstr.push_back(const_cast<char*>(arg));  // NOLINT
    }
    tokens = parser::Parse(argc, argv_cstr.data());
    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0].name == "input.bmp");
    REQUIRE(tokens[1].name == "/tmp/output.bmp");
    REQUIRE(tokens[2].name == "-crop");
    REQUIRE(tokens[3].name == "-gs");
    REQUIRE(tokens[4].name == "-blur");
}

TEST_CASE("File is not BMP exception") {
    std::string file_name = "not_bmp_file.png";
    reading_and_writing::Reader reader(file_name);
    REQUIRE_THROWS_AS(reader.Read(), std::invalid_argument);
}

TEST_CASE("Invalid block size for Mosaic filter exception") {
    Image img(image::utils::BASIC_WIDTH, image::utils::BASIC_HEIGHT);
    filter::Mosaic mosaic(image::utils::BASIC_INCOR_1);
    REQUIRE_THROWS_AS(mosaic.Apply(img), std::invalid_argument);
}

TEST_CASE("Non-positive value for crop filter exception") {
    Image img(image::utils::BASIC_WIDTH, image::utils::BASIC_HEIGHT);
    filter::Crop crop(image::utils::BASIC_INCOR_1, image::utils::BASIC_INCOR_2);
    REQUIRE_THROWS_AS(crop.Apply(img), std::invalid_argument);
}

TEST_CASE("Image constructor creates image with positive dimensions", "[image]") {
    SECTION("Valid dimensions") {
        size_t width = image::utils::BASIC_WIDTH;
        size_t height = image::utils::BASIC_HEIGHT;

        Image img(width, height);

        REQUIRE(img.GetWidth() == width);
        REQUIRE(img.GetHeight() == height);
    }
    SECTION("Invalid dimensions") {
        REQUIRE_THROWS_AS(Image(0, 100), std::invalid_argument);
        REQUIRE_THROWS_AS(Image(100, 0), std::invalid_argument);
        REQUIRE_THROWS_AS(Image(0, 0), std::invalid_argument);
    }
}

TEST_CASE("GetColor and SetColor methods work correctly", "[image]") {
    Image img(2, 2);
    SECTION("Setting and getting color") {
        Color color(image::utils::BASIC_COLOR_1, image::utils::BASIC_COLOR_2, image::utils::BASIC_COLOR_3);

        img.SetColor(0, 0, color);
        const Color& retrieved_color = img.GetColor(0, 0);

        REQUIRE((retrieved_color.red == color.red && retrieved_color.blue == color.blue &&
                 retrieved_color.green == color.green));
    }
    SECTION("Setting color out of range") {
        Color color(image::utils::MAX_COLOR_VALUE, image::utils::MAX_COLOR_VALUE, image::utils::MAX_COLOR_VALUE);
        REQUIRE_THROWS_AS(img.SetColor(2, 2, color), std::out_of_range);
    }
}

TEST_CASE("Copy constructor creates a deep copy of the image", "[image]") {
    Image img(2, 2);
    Color color(image::utils::BASIC_COLOR_1, image::utils::BASIC_COLOR_2, image::utils::BASIC_COLOR_3);
    img.SetColor(0, 0, color);
    Image img_copy(img);
    REQUIRE(img_copy.GetWidth() == img.GetWidth());
    REQUIRE(img_copy.GetHeight() == img.GetHeight());
}

TEST_CASE("Negative value for Mosaic filter exception") {
    Image img(image::utils::BASIC_WIDTH, image::utils::BASIC_HEIGHT);
    filter::Mosaic mosaic(-1);
    REQUIRE_THROWS_AS(mosaic.Apply(img), std::invalid_argument);
}

