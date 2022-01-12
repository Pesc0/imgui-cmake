# imgui-cmake

Simple project with cmake files to build imgui's example_sdl_opengl3 on multiple platforms. 

This should work on:

| Platform     | Status                              |
| ------------ | ----------------------------------- |
| Windows      | Not tested in a while, was working  |
| Linux        | Tested, working                     |
| Mac OS       | Never tested                        |
| Raspberry Pi | Tested on Pi3, working              |

# How to Build

To test the example:
```
git clone https://github.com/Pesc0/imgui-cmake --recurse-submodules
cd imgui-cmake
git submodule foreach git pull origin HEAD
mkdir build && cd build
cmake -D BUILD_EXAMPLES=ON ..
cmake --build . -j4
./example_sdl_opengl3
```

To add the library to your project simply add to your CMakeLists.txt: 

```add_subdirectory("path/to/imgui-cmake")```

Then link against the provided target: 

```target_link_libraries(YourTarget IMGUI)```

# Raspberry support

Install dependencies: ```libxext-dev libgles-dev libgles2-mesa-dev```

SDL is built from source since apparently the build in apt repos doesnt have the VIDEO_RPI option enabled. 

When using the broadcom drivers you may have to ```export SDL_VIDEODRIVER=rpi``` before running the program.

On a Raspberry Pi 3 the performance is around 100-130 fps at 1080p for the imgui demo. It can drop down to as low as 30 fps or even less if certain demanding features are being displayed. One example of such features are the colored buttons present in the demo under `layout & scrolling -> scrolling`.

Some important things to note if you are building for raspberry:

- On raspberry to get decent performance we have to use the GPU with OpenGLES. On Pi3 or older this means running the program at fullscreen with broadcom drivers, since when windowed it is software rendered. I was not able to get it working with KMS drivers. On Pi4 it should work both windowed and fullscreen without problems, independently of the driver used.
- In old raspbian there's a bug with the latest versions of the gcc compiler. Basically the `<limits.h>` file has been modified, and the `PATH_MAX` macro is missing. This causes an error when compiling some SDL files. To fix this make sure you are using gcc-4.9 or an **earlier** version. When running cmake specify: `-D CMAKE_C_COMPILER=gcc-4.9 -D CMAKE_CXX_COMPILER=g++-4.9`. An alternative would be to add `#define PATH_MAX 4096` at the beginning of the broken SDL files, although this is not recommended since it modifies the library. This issue is not present in the new RaspiOS.

For more accurate information refer to [this](https://github.com/ocornut/imgui/pull/2837) thread.
