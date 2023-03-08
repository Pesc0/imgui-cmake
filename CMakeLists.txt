cmake_minimum_required(VERSION 3.16.3)

project(imgui-cmake LANGUAGES C CXX)


# Use OpenGLES instead of OpenGL. 
#set(USE_GLES ON)


# ===== RASPBERRY SPECIFIC =====

# Enable if building for Raspberry. This will automatically use GLES instead of GL.
#set(RASPBIAN ON)

# Link against brcmGLESv2 instead of GLESv2. 
# Note that Broadcom drivers are NOT available on the 64-bit version of RaspberrypiOS (aarch64), they're only available on 32-bit (armv7l).
#set(RPI_USE_BROADCOM_DRIVER ON)

# Enable if your Raspberry supports NEON. Generally from Pi2 onwards this is supported. 
# This enables optimizations in the SDL library. 
#set(RPI_HAS_NEON ON)


add_subdirectory("libs")


#=================== EXAMPLE ===================

if(BUILD_EXAMPLES)
    add_executable(example_sdl3_opengl3)
    target_sources(example_sdl3_opengl3 PUBLIC ${CMAKE_SOURCE_DIR}/libs/imgui/examples/example_sdl3_opengl3/main.cpp)
    target_link_libraries(example_sdl3_opengl3 IMGUI)
    set_target_properties(example_sdl3_opengl3 PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()