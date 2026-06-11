add_executable(lftl_test
        main.cpp
        ${CMAKE_SOURCE_DIR}/src/formats/ltl/parser.cpp
)

set_target_properties(lftl_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(lftl_test PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)