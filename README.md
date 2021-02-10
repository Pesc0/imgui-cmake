# imgui-raspberry

This should work on:
- Windows (tested, working)
- Linux 
- Mac OS
- Raspberry Pi (tested, working)

I wrote the Cmake files and (to add raspberry support) modified
- gl3w.c
- main.cpp

according to the instructions found [here](https://github.com/ocornut/imgui/issues/2822#issuecomment-537840340).

***CAVEAT***: On raspberry to get decent performance we have to use the GPU with OpenGLES. Unfortunately the only way to do this is to run the program at fullscreen. To run the application windowed we would need to use OpenGL, which is not hardware accelerated and terribly slow.


# How to Build

***NOTE***: On Raspberry there's a bug with the latest versions of the gcc compiler. 
Basically the `<limits.h>` file has been modified, and the `PATH_MAX` macro is no longer there. 
This causes an error when compiling `SDL2-2.0.9/src/haptic/linux/SDL_syshaptic.c` .

**TO FIX THIS** you have two alternatives:
1. Make sure you are using gcc-4.9 or an **earlier** version.
2. Modify `SDL2-2.0.9/src/haptic/linux/SDL_syshaptic.c` and add `#define PATH_MAX 4096` at the beginning of the file.

To build example_sdl_opengl3:
```
cd example_sdl_opengl3
mkdir build && cd build
cmake ..
cmake --build . -j4
```

