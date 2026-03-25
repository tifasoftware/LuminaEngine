# State of Linux Support
*Last updated 3/25/2026*

## Preface
While Lumina Engine can easily be compiled and run on Linux, there are still some decisions that yet to be made in terms of distribution.
Linux is not necessarily a single OS (like Windows and Mac), instead it is a family of operating systems that share common components (Linux Kernel, GNU, X11/Wayland, etc.)

There has been issues recently with the developer of the DuckStation emulator. 
They ultimately decided to blacklist compiling for Linux out of fatigue of Linux users sending issues to them, instead of their distro maintainer. 

To prevent this issue from occurring I will lay down my policy on maintaining for Linux.

Below are the scenarios:

## Scenarios

### I Compiled Lumina Engine from the Official Repository and I ran into a bug.
If you compiled and ran Lumina from the official GitHub repository, and found a bug, report it here under Issues, and it will soon be addressed.
However, make sure you have the SDL2, SDL2_image, and SDL2_mixer libraries installed, as well as the neccessary build toolchain.

### I Installed Lumina Engine from the AUR, and it failed to build.
Send your complaint/issue to the AUR maintainer. I have not authored any official AUR pkgbuilds yet.

### I Installed Lumina Engine from the official Ubuntu, Debian, and/or Fedora repos.
Contact the responsible packager first. If they say it is an issue with the codebase, then come to us.

### I Installed Lumina Engine for this niche and little known Linux distro and it doesn't work.
Womp womp.

On a more serious note, try running it under a Ubuntu/Fedora/Arch container through Distrobox or KVM.
