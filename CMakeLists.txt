cmake_minimum_required(VERSION 3.7)
project(OpenGLSetup)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp GLAD/src/glad.c
        "classes and helper functions/GameBoard.cpp"
        "classes and helper functions/GameBoard.h")
set(HEADER_FILES shader.h
        "classes and helper functions/FPSCounter.cpp"
        "classes and helper functions/FPSCounter.h"
        "classes and helper functions/GlfwSetup.cpp"
        "classes and helper functions/GlfwSetup.h"
        "classes and helper functions/GameBoard.h")

include_directories(include)
include_directories(GLAD/include)
include_directories(glm/include)
include_directories(classes and helper functions)

add_subdirectory(dependencies)

add_executable(OpenGLSetup ${SOURCE_FILES} ${HEADER_FILES}
        "classes and helper functions/GameBoard.cpp"
        "classes and helper functions/GameBoard.h")
target_link_libraries(OpenGLSetup glfw)

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
