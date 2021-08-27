cmake_minimum_required(VERSION 3.16.3)

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


add_subdirectory("libs")

