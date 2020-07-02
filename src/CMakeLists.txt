cmake_minimum_required(VERSION 3.10)

project(Main)

file(GLOB_RECURSE sources Main/*.cpp Main/*.hpp)
file(GLOB_RECURSE data Assets/*)

add_executable(Main ${sources} ${data})

target_include_directories(Main PUBLIC Main)

add_custom_command(
    TARGET Main
    POST_BUILD
    COMMAND cp -rf "${CMAKE_SOURCE_DIR}/Assets" "${CMAKE_BINARY_DIR}/Assets")

target_link_libraries(Main sfml-graphics)
target_link_libraries(Main sfml-audio)
target_link_libraries(Main sfml-window)
target_link_libraries(Main sfml-system)
target_link_libraries(Main X11)
target_link_libraries(Main GL)
target_link_libraries(Main pthread)
