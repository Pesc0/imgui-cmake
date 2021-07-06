

#=================== SDL2 ===================

cmake_policy(SET CMP0077 NEW)
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW)

if(RASPBIAN)
    set(VIDEO_RPI       ON)
endif()

set(SDL2_DIR "SDL")
add_subdirectory(${SDL2_DIR})


#=================== OpenGL ===================

# Do not search for OpenGL on raspbian. Use GLES instead.
if(RASPBIAN)
    set(USE_GLES ON) 
endif()

if(NOT USE_GLES)
    find_package(OpenGL REQUIRED)

    #Use gl3w as GL loader. It is the default in imgui's examples.
    set(GL3W_DIR "imgui/examples/libs/gl3w")
    add_library(GL3W STATIC)

    target_sources(GL3W PRIVATE ${GL3W_DIR}/GL/gl3w.c)
    target_include_directories(GL3W PUBLIC ${GL3W_DIR})
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


if(RASPBIAN)
    target_compile_definitions(IMGUI PUBLIC -D__RASPBIAN__)
endif()


if(USE_GLES)
    target_compile_definitions(IMGUI PUBLIC -DIMGUI_IMPL_OPENGL_ES2)

    if(RASPBIAN AND USE_BROADCOM_DRIVER)
        target_link_directories(IMGUI PUBLIC /opt/vc/lib)
        target_link_libraries(IMGUI PUBLIC brcmGLESv2 brcmEGL)
    else()
        target_link_libraries(IMGUI PUBLIC GLESv2)
    endif()

else()
    target_compile_definitions(IMGUI PUBLIC -DIMGUI_IMPL_OPENGL_LOADER_GL3W)
    target_link_libraries(IMGUI PUBLIC GL3W)

endif()


target_link_libraries(IMGUI PUBLIC SDL2main SDL2 ${CMAKE_DL_LIBS})


