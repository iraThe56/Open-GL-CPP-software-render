# Library management

# GlFW Via Git Submodule for window management
add_subdirectory(glfw/)

# GLAD Via pregen for OpenGL Compat
add_subdirectory(glad/)

# GLM Via Git Submodule for mathematic functions
add_subdirectory(glm/)

# -----------------------------
# ImGui (FetchContent)
# -----------------------------
include(FetchContent)

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG        v1.90.9
)
FetchContent_MakeAvailable(imgui)

add_library(imgui_lib STATIC
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp

        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(imgui_lib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
)

# Tell ImGui OpenGL backend which loader you're using (GLAD)
target_compile_definitions(imgui_lib PUBLIC IMGUI_IMPL_OPENGL_LOADER_GLAD)

# If you hit the GLFW gamepad compile errors again, enable this:
# target_compile_definitions(imgui_lib PUBLIC IMGUI_IMPL_GLFW_DISABLE_GAMEPAD)

find_package(OpenGL REQUIRED)

target_link_libraries(imgui_lib PUBLIC
        glfw
        OpenGL::GL
)
