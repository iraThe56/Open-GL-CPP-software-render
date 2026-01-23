cmake_minimum_required(VERSION 3.7)
project(OpenGLSetup)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

set(SOURCE_FILES src/main.cpp GLAD/src/glad.c
        "src/core/GameBoard.cpp"
        "src/core/GameBoard.h")
set(HEADER_FILES src/shader.h
        "src/core/FPSCounter.cpp"
        "src/core/FPSCounter.h"
        "src/core/GlfwSetup.cpp"
        "src/core/GlfwSetup.h"
        "src/core/GameBoard.h"
        src/main.cpp)

include_directories(include)
include_directories(GLAD/include)
include_directories(glm/include)
#include_directories(imgui)
include_directories(classes and helper functions)

add_subdirectory(dependencies)

add_executable(OpenGLSetup ${SOURCE_FILES} ${HEADER_FILES}
        "src/core/GameBoard.cpp"
        "src/core/GameBoard.h")
target_link_libraries(OpenGLSetup glfw )

# Put the exe in build/<CONFIG> (Debug/Release)
set_target_properties(OpenGLSetup PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/build/$<CONFIG>"
)

# Copy assets next to the exe after build
add_custom_command(TARGET OpenGLSetup POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/resources"
        "$<TARGET_FILE_DIR:OpenGLSetup>/resources"
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/shaders"
        "$<TARGET_FILE_DIR:OpenGLSetup>/shaders"
)
