cmake_minimum_required(VERSION 3.17.0)

project(imgui-cmake LANGUAGES C CXX)


# ============ Raspbian detection ============

if(UNIX AND NOT APPLE)
        execute_process(COMMAND bash "-c" "cat /etc/os-release | grep '^ID=' | sed 's/ID=//'" OUTPUT_VARIABLE __OS_RELEASE)
        if(__OS_RELEASE MATCHES "raspbian")
                set(RASPBIAN ON)
        endif()
endif()

# ============================================


#Use openGLES instead of desktop GL. Automatically set if compiling on raspbian
#set(USE_GLES ON)

#Use the brcmGLESv2 driver instead of GLESv2. May be required on versions older than pi4
#set(USE_BROADCOM_DRIVER ON)

#Disable all except 'rpi' SDL backends on rasbpian, this avoids having to 'export SDL_VIDEODRIVER=rpi' before running the executable
#set(FORCE_RPI_DRIVER ON)


add_subdirectory("libs")
add_subdirectory("src")

if(BUILD_EXAMPLES)
        add_subdirectory("examples")
endif()
