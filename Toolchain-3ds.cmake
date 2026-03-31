set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

set(CMAKE_C_COMPILER_WORKS TRUE)
set(CMAKE_CXX_COMPILER_WORKS TRUE)

# devkitARM stuff
set(DEVKITPRO $ENV{DEVKITPRO})
set(DEVKITARM $ENV{DEVKITARM})

set(CMAKE_C_COMPILER "${DEVKITARM}/bin/arm-none-eabi-gcc")
set(CMAKE_CXX_COMPILER "${DEVKITARM}/bin/arm-none-eabi-g++")
set(CMAKE_AR "${DEVKITARM}/bin/arm-none-eabi-ar")
set(CMAKE_ASM_COMPILER "${DEVKITARM}/bin/arm-none-eabi-as")
set(CMAKE_LINKER "${DEVKITARM}/bin/arm-none-eabi-ld")
set(CMAKE_OBJCOPY "${DEVKITARM}/bin/arm-none-eabi-objcopy")

set(CMAKE_EXE_LINKER_FLAGS "-specs=3dsx.specs -L${DEVKITPRO}/libctru/lib")

include_directories("${DEVKITPRO}/libctru/include" "${DEVKITPRO}/portlibs/armv6/include")
link_directories("${DEVKITPRO}/libctru/lib" "${DEVKITPRO}/portlibs/armv6/lib")