
add_executable(yang.elf main.cpp)

set_target_properties(yang.elf PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

target_link_directories(yang.elf PRIVATE
        $ENV{PS2SDK}/ports/lib/
        $ENV{PS2SDK}/ee/lib/
        $ENV{PS2SDK}/common/lib/
        $ENV{PS2SDK}/../gsKit/lib/
)

target_link_libraries(yang.elf PRIVATE
		SDL2 SDL2_image SDL2_mixer
		modplug xmp audsrv atomic gskit dma dmakit
		debug kernel patches config draw
		ps2_drivers
		SDL2main
		stdc++ m c
		elf-loader2
)
