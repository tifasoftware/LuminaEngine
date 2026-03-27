# Lumina Engine

> ⚠️ Early prototype — expect breaking changes and missing features.

A 2D RPG game engine for the PlayStation Portable, built with C++ and SDL2. Designed with portability in mind for future platforms.

---

## Features

- SDL2 based rendering
- Lua 5.5 scripting (WIP)
- Tile map system with custom LMAP format
- Memory-efficient Texture management
- Multiplatform controller and keyboard input
- Runs on most major OSes and Homebrew

## Planned Features

- [ ] WAD style asset packaging
- [ ] NPC system
- [X] Dialogue system (Work in Progress)
- [ ] Battle system
- [ ] Save/load system

---

## Platform Support

| Platform                                                   | Status                                                                                                                                                                   |
|------------------------------------------------------------|--------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| PSP                                                        | ✅ Primary target                                                                                                                                                         |
| Windows                                                    | ✅ Primary target                                                                                                                                                         |
| macOS                                                      | ✅ Primary target                                                                                                                                                         |
| Linux                                                      | ⚠️ Officially supported only if compiled. Not packaging for major distros yet. [State of Linux Support](docs/linux_support.md)                                           |
| FreeBSD / OpenBSD / NetBSD / Solaris / OpenIndiana / Haiku | 🔜 May have potential ports only as proof of concept (or fun).                                                                                                           |
| iOS / iPadOS                                               | ❌ Probably too restrictive. Players are encouraged to run the PSP version thru [PPSSPP](https://apps.apple.com/us/app/ppsspp-psp-emulator/id6496972903) instead.         |
| Android                                                    | ❔ Feasibillity will be researched. Players are encouraged to run the PSP version thru [PPSSPP](https://play.google.com/store/apps/details?id=org.ppsspp.ppsspp) for now. |
| NDS                                                        | ❌ Not enough system RAM                                                                                                                                                  |
| 3DS                                                        | 🔜 Planned (More powerful than PSP, and has [SDL2](https://wiki.libsdl.org/SDL2/README-n3ds))                                                                            |
| Wii                                                        | ❔ Feasibility will be researched                                                                                                                                         |
| PS3                                                        | ❔ Feasibility will be researched                                                                                                                                         |
| PS Vita                                                    | ⚠️ Not officially supported, but should run with the Adrenaline Emulator.                                                                                                |
| Legacy versions of Windows and macOS                       | ❔ Feasibility will be researched                                                                                                                                                                         |
---

## Dependencies

- [PSPDEV toolchain](https://github.com/pspdev/pspdev)
- SDL2 (bundled with PSPDEV)
- SDL2_image (bundled with PSPDEV)
- Lua 5.4 (bundled with PSPDEV)

---

## Building

### PSP
```bash
mkdir build && cd build
psp-cmake ..
make
```
The build will output `EBOOT.PBP` for PSP and copy assets to the build directory automatically.

## Mac
```bash
mkdir build && cd build
cmake ..
make
```
The build will output a `LuminaEngine.app` with the libraries and assets included inside.

## Windows
via WSL (Ubuntu)
```bash
sudo apt update
sudo apt install mingw-w64 cmake make
mkdir build && cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake/Toolchain-mingw64.cmake
make
```
The build will output a `LuminaEngine.exe` with the dlls and assets alongside.

## Linux
```bash
mkdir build && cd build
cmake ..
make
```
The build will output an `LuminaEngine` executable with the assets alongside.

---

## Map Format

LuminaEngine currently uses a custom binary map format (`.lmap`). The LMAP format is under **heavy development** and is prone to radical changes so it is recommended to recompile your maps every time Lumina Engine gets updated.

To create a map, you must export to the TMJ/JSON format with Tiled utilizing a [texture tile atlas](https://en.wikipedia.org/wiki/Texture_atlas) as your tileset.

Then you write a Lumina Atlas Definition for that PNG atlas or a LAD, for short.

Example: `tileatlas.lad`
```
!ATLAS
mapatlas.png
NONE
NONE
NORTH
SOUTH
EAST
WEST
NEO
NWO
SEO
SWO
SWI
SEI
NWI
NEI
```


```bash
mkdir tool_build && cd tool_build
cmake ..
make
./lmap_compile TMJFILE.tmj TILEATLAS.lad MAP.lmap
```

---

## Contributing

Contributions are welcome! If you'd like to help:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/my-feature`)
3. Commit your changes (`git commit -m "add my feature"`)
4. Push to the branch (`git push origin feature/my-feature`)
5. Open a Pull Request

Please keep PSP hardware constraints in mind — 32MB RAM, 480x272 resolution.
