

#=================== SDL3 ===================

if(RASPBIAN AND RPI_HAS_NEON)
    add_compile_options(-mfpu=neon)
endif()

set(SDL3_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SDL)
add_subdirectory(${SDL3_DIR})


#=================== IMGUI ===================

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
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
                            PUBLIC ${SDL3_DIR}/include/SDL3
                            )


if(USE_GLES OR RASPBIAN)
    target_compile_definitions(IMGUI PUBLIC -DIMGUI_IMPL_OPENGL_ES2)

    if(RASPBIAN AND RPI_USE_BROADCOM_DRIVER)
        target_link_directories(IMGUI PUBLIC /opt/vc/lib)
        target_link_libraries(IMGUI PUBLIC brcmGLESv2 brcmEGL)
    else()
        target_link_libraries(IMGUI PUBLIC GLESv2)
    endif()
else()
    find_package(OpenGL REQUIRED)
    target_link_libraries(IMGUI PUBLIC ${OPENGL_LIBRARIES})
endif()


target_link_libraries(IMGUI PUBLIC SDL3 ${CMAKE_DL_LIBS})


