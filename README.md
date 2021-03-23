# imgui-cmake

Simple project with cmake files to build imgui's example_sdl_opengl3 on multiple platforms. A thin multithreaded wrapper is also provided. This should work on:
- Windows (tested, working)
- Linux (tested, working)
- Mac OS
- Raspberry Pi (tested only on Pi3, working)

# How to Build

To test the examples:
```
git clone https://github.com/Pesc0/imgui-cmake --recurse-submodules
cd imgui-cmake
mkdir build && cd build
cmake -D BUILD_EXAMPLES=ON ..
cmake --build . -j4
./examples/example_wrapper
```

To add the library to your project simply add this line to your CMakeLists.txt: 
```
add_subdirectory("path/to/imgui-cmake")
```
then link against one of the provided targets: 
```
target_link_libraries(YourTarget IMGUI) 
target_link_libraries(YourTarget IMGUIWRAPPER)
```

# Raspberry support

Some important things to note if you are building for raspberry:
- SDL has to be rebuilt with rpi driver support. Hence it is inclued as a submodule and compiled with cmake.
- On raspberry to get decent performance we have to use the GPU with OpenGLES. Unfortunately the only way to do this is to run the program at fullscreen. 
To run the application windowed we would need to use OpenGL, which is not hardware accelerated and terribly slow.
- To add rasberry support the gl3w library has been modified. It now links against `libbrcmGLESv2.so` when the macro `__RASPBIAN__` is defined.
The exact modifications can be seen in the patch file found [here](https://github.com/ocornut/imgui/issues/2822#issuecomment-573319787).
- On Raspberry there's a bug with the latest versions of the gcc compiler. Basically the `<limits.h>` file has been modified, and the `PATH_MAX` macro is no longer there. 
This causes an error when compiling `SDL/src/haptic/linux/SDL_syshaptic.c`. To fix this make sure you are using gcc-4.9 or an **earlier** version. When running cmake specify: `-D CMAKE_C_COMPILER=gcc-4.9 -D CMAKE_CXX_COMPILER=g++-4.9`. An alternative would be to add `#define PATH_MAX 4096` at the beginning of the SDL file, although this is not recommended since it modifies the library.
- The examples main files have some raspbian specific code in two places: the first is needed to choose the correct glsl shader version and to set the proper GL attributes in SDL. The second sets the `SDL_WINDOW_FULLSCREEN_DESKTOP` flag when creating the SDL window, since the raspberry only renders fullscreen. If this is not done and the window resolution doesn't match the monitor resolution the video will still be fullscreen but the mouse cusror will be offset from the actual registered position.

# About the examples

- `example_sdl_opengl3`: except for the minor raspbian specific modifications listed above the code is exactly the same as the original imgui example. It does not use the provided wrapper.
- `example_wrapper_simple`: showcases how to use the multithreaded wrapper by displaying the imgui demo window. If all you want to do is get imgui working you should use this code.
- `example_wrapper_withGL`: showcases how to use the multithreaded wrapper and additionally to the imgui demo a red triangle is drawn on the background, to show how OpenGL code can be used with the library. If you are doing anything remotely serious with OpenGL it is recommended you write your own engine and use the raw SDL and ImGui interfaces used in `example_sdl_opengl3`.