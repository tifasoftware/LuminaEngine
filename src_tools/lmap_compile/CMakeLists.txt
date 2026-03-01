add_executable(lmap_compile main.cpp)

set_target_properties(lmap_compile PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(lmap_compile PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)