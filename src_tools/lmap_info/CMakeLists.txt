add_executable(lmap_info main.cpp)

set_target_properties(lmap_info PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_include_directories(lmap_info PRIVATE 
    ${CMAKE_SOURCE_DIR}/src
)