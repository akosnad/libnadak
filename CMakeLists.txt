cmake_minimum_required(VERSION 3.22)
project(nadak_lib)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")


include_directories(itk_graphicslib)
add_subdirectory(itk_graphicslib graphicslib)
link_libraries(
    graphics
)

add_compile_options("-Wall")

file(GLOB sources *.cpp)
list(REMOVE_ITEM sources main.cpp)

add_library(nadak_lib ${sources})
add_executable(test_widgets main.cpp)
target_link_libraries(test_widgets nadak_lib)

add_custom_command(
    TARGET nadak_lib POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${CMAKE_CURRENT_SOURCE_DIR}/LiberationSans-Regular.ttf
    ${CMAKE_BINARY_DIR}/.
)
