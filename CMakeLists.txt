cmake_minimum_required(VERSION 3.17.0)

project(imgui-cmake LANGUAGES C CXX)


# ============ raspbian detection ============

if(UNIX AND NOT APPLE)
        execute_process(COMMAND bash "-c" "cat /etc/os-release | grep '^ID=' | sed 's/ID=//'" OUTPUT_VARIABLE __OS_RELEASE)
        if(__OS_RELEASE MATCHES "raspbian")
                set(RASPBIAN ON)
        endif()
endif()

# ============================================


#set(BUILD_SHARED_LIBS OFF)
add_subdirectory("libs")
add_subdirectory("src")


add_subdirectory("examples")

