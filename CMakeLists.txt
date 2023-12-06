cmake_minimum_required(VERSION 3.10)

project(GameBoot)

set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL)
if(MINGW)
    set(BIN_DIR "mingw-W64")
    find_library(GLFW NAMES libglfw3.a PATHS lib/glfw/mingw-w64)
    find_library(ASSIMP NAMES libassimp.dll.a PATHS lib/assimp/mingw-w64)
elseif (MSVC)
    set(BIN_DIR "vc2022")
    find_library(GLFW NAMES glfw3.lib PATHS lib/glfw/vc2022)
    find_library(ASSIMP NAMES assimp-vc143-mt.lib PATHS lib/assimp/vc2022)
elseif (APPLE)
    set(BIN_DIR "macos")
    find_library(GLFW NAMES libglfw3.a PATHS lib/glfw/macos-universal)
    find_library(ASSIMP NAMES libassimp.5.3.0.dylib PATHS lib/assimp/macos-universal)
    find_library(COCOA_FRAMEWORK Cocoa)
    find_library(IOKIT_FRAMEWORK IOKit)
    find_library(CORE_FOUNDATION_FRAMEWORK CoreFoundation)
    find_library(CORE_VIDEO_FRAMEWORK CoreVideo)
    list(APPEND LIBS
            "${COCOA_FRAMEWORK}"
            "${IOKIT_FRAMEWORK}"
            "${CORE_FOUNDATION_FRAMEWORK}"
            "${CORE_VIDEO_FRAMEWORK}")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_SOURCE_DIR}/bin/${BIN_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_SOURCE_DIR}/bin/${BIN_DIR}")
include_directories(lib)

list(APPEND LIBS
    "${OPENGL_LIBRARIES}"
    "${GLFW}" "${ASSIMP}")

add_executable(${PROJECT_NAME}
        lib/glad/gl.c
        src/base/GameApp.cpp
        src/base/ShaderProgram.cpp
        src/main.cpp
        src/MyGameApp.cpp
        src/base/Camera.cpp
        src/base/Camera.h
        src/base/Geometry.cpp
        src/base/Geometry.h)

target_link_libraries(${PROJECT_NAME} ${LIBS})

set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_DEBUG ${PROJECT_NAME}-debug )
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME_RELEASE ${PROJECT_NAME}-release )

if(MINGW)
#    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mwindows")
elseif (MSVC)
    set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME})
#    set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif ()