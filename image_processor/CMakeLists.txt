set(SOURCE_FILES
        Image/image.h
        Image/color.cpp
        Image/image.cpp
        Reader_and_Writer/Reader.h
        Reader_and_Writer/Reader.cpp
        Reader_and_Writer/Utils.h
        Reader_and_Writer/Writer.cpp
        Reader_and_Writer/Writer.h
        Parser/Parser.h
        Parser/Parser.cpp
        image_processor.h
        Filter/Filter.cpp
        Filter/Filter.h
)

add_executable(image_processor image_processor.cpp ${SOURCE_FILES})

add_catch(test_parser test_script/unit_tests/test.cpp
        ${SOURCE_FILES})