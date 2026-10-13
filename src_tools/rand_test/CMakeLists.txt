add_executable(rand_test main.cpp)

set_target_properties(rand_test PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(rand_test PRIVATE
        ${CMAKE_SOURCE_DIR}/src
)