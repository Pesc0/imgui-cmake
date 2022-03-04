cmake_minimum_required(VERSION 3.16.3)

project(imgui-cmake LANGUAGES C CXX)


# Enable if building for raspberry
#set(RASPBIAN ON)

# Use openGLES instead of desktop GL. This gets automatically set if compiling on raspbian
#set(USE_GLES ON)

# Use the brcmGLESv2 driver instead of GLESv2. May be required to get hardware acceleration on versions older than pi4
# Note that broadcom drivers are NOT available on the 64-bit version of raspberry pi os (aarch64). They're only
# available on 32-bit (armv7l)
#set(USE_BROADCOM_DRIVER ON)


add_subdirectory("libs")

