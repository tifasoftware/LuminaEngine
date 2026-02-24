# Lumina Engine

> ⚠️ Early prototype — expect breaking changes and missing features.

A 2D RPG game engine for the PlayStation Portable, built with C++ and SDL2. Designed with portability in mind for future platforms.

---

## Features

- SDL2 based rendering
- Tile map system with custom LMAP format
- Texture management
- PSP controller input
- Platform abstraction layer for future ports

## Planned Features

- [ ] WAD style asset packaging
- [ ] Lua 5.4 scripting
- [ ] Camera and scrolling
- [ ] Collision detection
- [ ] Entity and NPC system
- [ ] Dialogue system
- [ ] Battle system
- [ ] Audio manager
- [ ] Save/load system

---

## Platform Support

| Platform | Status |
|---|---|
| PSP | ✅ Primary target |
| 3DS | 🔜 Planned |
| Windows / Mac / Linux | 🔜 Planned |

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

### Desktop (coming soon)
```bash
mkdir build && cd build
cmake ..
make
```

The build will output `EBOOT.PBP` for PSP and copy assets to the build directory automatically.

---

## Map Format

LuminaEngine currently uses a custom text based map format (`.lmap`) for development, with a binary format planned for release builds.

```
LMAP
floor.png
wall.png
LAYOUT
1,1,1,1,1
1,0,0,0,1
1,1,1,1,1
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

## Credits

Test Character Sprite created using [[https://www.avatarsinpixels.com/]]
