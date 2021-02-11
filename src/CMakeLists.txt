

add_library(IMGUIWRAPPER STATIC)
target_sources(IMGUIWRAPPER PRIVATE ImGuiWrapper.cpp)
target_include_directories(IMGUIWRAPPER PUBLIC . )                          
target_link_libraries(IMGUIWRAPPER PUBLIC IMGUI)
