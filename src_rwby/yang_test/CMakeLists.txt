add_executable(yang.elf main.cpp)

set_target_properties(yang.elf PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_directories(yang.elf PRIVATE
        $ENV{PS2SDK}/ports/lib/
        $ENV{PS2SDK}/ports_iop/lib/
        $ENV{PS2SDK}/ee/lib/
        $ENV{PS2SDK}/common/lib/
        $ENV{PS2SDK}/iop/lib/
        $ENV{PS2SDK}/../gsKit/lib/
)

target_link_libraries(yang.elf PRIVATE
        SDL2 SDL2_image SDL2_mixer
        lua
        ps2_drivers xmp modplug gs gskit dmakit patches
        kernel
)