cmake_minimum_required(VERSION 3.22)
project(nadak_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")


include_directories(itk_graphicslib)
add_subdirectory(itk_graphicslib graphicslib)
link_libraries(
    graphics
)

add_compile_options("-Wall")

add_library(nadak_lib widgets.cpp window.cpp checkbox.cpp textbox.cpp inputtextbox.cpp button.cpp numberinput.cpp dropdown.cpp box.cpp container.cpp)
add_executable(test_widgets main.cpp)
target_link_libraries(test_widgets nadak_lib)
