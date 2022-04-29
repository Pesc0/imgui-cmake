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

