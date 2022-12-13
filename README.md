# imgui-cmake

Simple project with CMake files to build ImGui's example_sdl_opengl3 on multiple platforms. 
The main focus is RaspberryPi support, but this will work just fine on Windows, Mac and Linux.

To test the example:
```
git clone https://github.com/Pesc0/imgui-cmake --recurse-submodules
cd imgui-cmake
#git submodule foreach git pull origin HEAD
mkdir build && cd build
cmake -D BUILD_EXAMPLES=ON ..
cmake --build . -j4
./example_sdl_opengl3
```

To add the library to your project simply add to your CMakeLists.txt: 
```
add_subdirectory("path/to/imgui-cmake")
target_link_libraries(YourTarget IMGUI)
```


## Raspberry support

### Building
You may need these dependencies: 

```
sudo apt install libxext-dev libgles-dev libgles2-mesa-dev libgdm-dev libgbm-dev libdrm-dev libudev-dev libasound2-dev libdbus-1-dev
```

VideoCore stuff (Broadcom drivers) which should be already installed by default: 

```
sudo apt install libraspberrypi0 libraspberrypi-bin libraspberrypi-dev
```

Other notes: In old raspbian there's a bug with the latest versions of the gcc compiler: the `<limits.h>` file has been modified, and the `PATH_MAX` macro is missing. This causes an error when compiling some SDL files. Possible solutions are:
- Use gcc-4.9 or an **earlier** version: when running cmake specify `-D CMAKE_C_COMPILER=gcc-4.9 -D CMAKE_CXX_COMPILER=g++-4.9`. This is not optimal since newer compilers tend to produce better code in general.
- Add `#define PATH_MAX 4096` at the beginning of the broken SDL files, or add the same define in the compiler options, but this is not an elegant solution. 
- Use the new RaspberrypiOS, where this issue is not present. 

### GPU acceleration
Regarding graphics, to render on Raspberry we have different options:
- No hardware acceleration, using the Mesa software renderer (slow)
- With GPU acceleration, which can be achieved in two ways (text adapted from [here](https://discourse.libsdl.org/t/sdl2-performances-on-raspberrypi/22992)):
  1. Use the old firmware-side Broadcom driver usually located in ```/opt/vc/lib```. This is an older driver that kind of works, but doesn’t integrate well with X11: you just get one fullscreen window, with or without X11. SDL has the rpi video backend for this driver. You may have to ```export SDL_VIDEODRIVER=rpi``` before running the executable to force SDL to use this backend, which doens't always get automatically selected. ```imgui-cmake``` builds SDL from source since the build in apt repos doesn't have the rpi backend compiled in (VIDEO_RPI option), although this may have been fixed in RaspberrypiOS. Note that Broadcom drivers are **not** available in the 64-bit version of RaspberrypiOS, only the 32-bit one.

  2. Use the new vc4 driver by Eric Anholt. Broadcom hired him to write an open source driver that uses open APIs (specifically: It’s a gallium driver). If you activate this driver (which deactivates the older driver), X11 itself and the x11 backend of SDL will get hardware acceleration. This only works from X11, of course. With SDL 2.0.5, there’s no support to run SDL applications from the console in this configuration. However, SDL 2.0.6 has a new KMSDRM driver which will make it possible. To activate this driver use the raspi-config program of the Raspbian distribution. Under “Advanced Options” -> “GL Driver” you can select the “GL (Full KMS)” option. It’s still somewhat experimental and the behavior might be slightly different compared to the older driver.

It is also reccommended in the [SDL Raspberry documentation](https://github.com/libsdl-org/SDL/blob/main/docs/README-raspberrypi.md) to assign 128MB of ram (or more) to the GPU.

### Expected performance
On a Raspberry Pi 3 the performance is around 100-130 fps at 1080p for the imgui demo. It can drop down to as low as 30 fps or even less if certain demanding features are being displayed. 

An example of such features is the colored buttons present in the demo under "layout & scrolling -> scrolling"
