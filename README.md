# imgui-cmake

Simple project with cmake files to build imgui's example_sdl_opengl3 on multiple platforms. This should work on:
- Windows (tested, working)
- Linux 
- Mac OS
- Raspberry Pi (tested, working)

***CAVEAT***: On raspberry to get decent performance we have to use the GPU with OpenGLES. Unfortunately the only way to do this is to run the program at fullscreen. To run the application windowed we would need to use OpenGL, which is not hardware accelerated and terribly slow.

To add rasberry support the gl3w library has been modified. For more information please read [this file](libs/gl3w/GL/README.md).

# How to Build

Clone the repo with the `--recurse-submodules` flag. Then:
```
cd imgui-cmake
mkdir build && cd build
cmake ..
cmake --build . -j4
```

***NOTE***: On Raspberry there's a bug with the latest versions of the gcc compiler. 
Basically the `<limits.h>` file has been modified, and the `PATH_MAX` macro is no longer there. 
This causes an error when compiling `SDL2-2.0.9/src/haptic/linux/SDL_syshaptic.c`. 
**TO FIX THIS** you have two alternatives:
1. Make sure you are using gcc-4.9 or an **earlier** version. When running cmake specify: `cmake -D CMAKE_C_COMPILER=gcc-4.9 -D CMAKE_CXX_COMPILER=g++-4.9 ..`
2. Modify `SDL2-2.0.9/src/haptic/linux/SDL_syshaptic.c` and add `#define PATH_MAX 4096` at the beginning of the file.
