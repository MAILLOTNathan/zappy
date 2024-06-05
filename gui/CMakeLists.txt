cmake_minimum_required(VERSION 3.27)

project(Onyx)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)

pkg_search_module(GLFW REQUIRED glfw3)

find_package(assimp REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-g3 -ggdb)
    message("Debug mode enabled")
endif()

add_subdirectory("ege/")

include_directories("ege/include/" "include/" "ege/imgui/" "ege/imgui/backends/")

add_executable(Onyx ${SOURCES})

set(LIBS ${LIBS} "GL" "glfw" "assimp" EGE)

target_link_libraries(Onyx PUBLIC ${LIBS})

# target_link_libraries(Onyx ${CMAKE_BINARY_DIR}/../etib-game-engine/build/libEGE-OpenGL.so)

set_target_properties(Onyx PROPERTIES OUTPUT_NAME "onyx")

set_target_properties(Onyx PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/../")
