cmake_minimum_required(VERSION 3.22)
project(bead2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")


include_directories(itk_graphicslib)
add_subdirectory(itk_graphicslib graphicslib)
link_libraries(
    graphics
)

add_library(widgets widgets.cpp)
add_executable(test_widgets main.cpp)
target_link_libraries(test_widgets widgets)

ADD_CUSTOM_TARGET(compile_commands ALL  COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_CURRENT_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json )
