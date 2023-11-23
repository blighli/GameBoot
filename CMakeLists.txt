cmake_minimum_required(VERSION 3.10)

project(GameBoot)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin")

find_package(OpenGL)
if(MINGW)
    find_library(GLFW NAMES libglfw3.a PATHS lib/glfw/mingw-w64)
elseif (MSVC)
    find_library(GLFW NAMES glfw3.lib PATHS lib/glfw/vc2022)
elseif (APPLE)
    find_library(GLFW NAMES libglfw3.a PATHS lib/glfw/macos-universal)
endif()

include_directories(lib)

list(APPEND LIBS
    "${OPENGL_LIBRARIES}"
    "${GLFW}")

add_executable(${PROJECT_NAME}
    src/main.cpp
    lib/glad/gl.c)

target_link_libraries(${PROJECT_NAME} ${LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJECT_NAME}-debug )
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${PROJECT_NAME}-release )