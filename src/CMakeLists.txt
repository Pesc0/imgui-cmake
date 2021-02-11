

add_library(IMGUIWRAPPER STATIC)

target_compile_features(IMGUIWRAPPER PUBLIC cxx_std_11)

target_sources(IMGUIWRAPPER PRIVATE ImGuiWrapper.cpp)
target_include_directories(IMGUIWRAPPER PUBLIC . )    

if(UNIX)
    target_link_libraries(IMGUIWRAPPER PUBLIC pthread)
endif()
target_link_libraries(IMGUIWRAPPER PUBLIC IMGUI)
