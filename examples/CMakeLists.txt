

add_executable(example_sdl_opengl3)
target_sources(example_sdl_opengl3 PUBLIC example_sdl_opengl3.cpp)
target_link_libraries(example_sdl_opengl3 IMGUI)

add_executable(example_wrapper_simple)
target_sources(example_wrapper_simple PUBLIC example_wrapper_simple.cpp)
target_link_libraries(example_wrapper_simple IMGUIWRAPPER)

add_executable(example_wrapper_withGL)
target_sources(example_wrapper_withGL PUBLIC example_wrapper_withGL.cpp)
target_link_libraries(example_wrapper_withGL IMGUIWRAPPER)