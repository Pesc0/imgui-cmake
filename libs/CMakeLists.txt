

#=================== SDL2 ===================

cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if(RASPBIAN)
    set(VIDEO_MIR       OFF)
    set(VIDEO_VULKAN    OFF)
    set(VIDEO_WAYLAND   OFF)
    set(VIDEO_OPENGL    OFF)
    set(VIDEO_RPI       ON)
endif()

set(SDL2_DIR "SDL")
add_subdirectory(${SDL2_DIR}) 


#=================== OpenGL ===================

# Do not search for OpenGL on raspbian. 
# There we will link with brcmGLESv2 and brcmEGL instead.

if(NOT RASPBIAN)
    find_package(OpenGL REQUIRED)
endif()


#=================== GL3W ===================

set(GL3W_DIR "gl3w")
add_library(GL3W STATIC)

target_sources(GL3W PRIVATE ${GL3W_DIR}/GL/gl3w.c)
target_include_directories(GL3W PUBLIC ${GL3W_DIR})

if(RASPBIAN)
    target_compile_definitions(GL3W PUBLIC -D__RASPBIAN__)
    target_link_libraries(GL3W PUBLIC brcmGLESv2 brcmEGL dl)
else()
    target_link_libraries(GL3W PUBLIC ${OPENGL_LIBRARIES})
endif()


#=================== IMGUI ===================

set(IMGUI_DIR "imgui")
add_library(IMGUI STATIC)

target_sources( IMGUI 
                PRIVATE
                    ${IMGUI_DIR}/imgui_demo.cpp
                    ${IMGUI_DIR}/imgui_draw.cpp
                    ${IMGUI_DIR}/imgui_tables.cpp
                    ${IMGUI_DIR}/imgui_widgets.cpp
                    ${IMGUI_DIR}/imgui.cpp

                PRIVATE
                    ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
                    ${IMGUI_DIR}/backends/imgui_impl_sdl.cpp
                )

target_include_directories( IMGUI 
                            PUBLIC ${IMGUI_DIR}
                            PUBLIC ${IMGUI_DIR}/backends
                            PUBLIC ${SDL2_DIR}/include
                            )
                            
target_compile_definitions(IMGUI PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GL3W)

if(RASPBIAN)
    target_compile_definitions(IMGUI PUBLIC -DIMGUI_IMPL_OPENGL_ES2)
    target_link_directories(IMGUI PUBLIC /opt/vc/lib)
endif()

target_link_libraries(IMGUI PUBLIC GL3W SDL2main SDL2)


