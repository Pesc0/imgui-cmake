


add_executable(example_sdl_opengl3)
target_sources(example_sdl_opengl3 PUBLIC main.cpp)
target_link_libraries(example_sdl_opengl3 IMGUI)


add_executable(testmain)
target_sources(testmain PUBLIC testmain.cpp)
target_link_libraries(testmain IMGUIWRAPPER)