cmake_minimum_required(VERSION 3.17)
project(game-framework-graphics)

ADD_LIBRARY(game-framework-graphics STATIC
    src/camera/PerspectiveCamera.cpp
    src/camera/CameraSetup.cpp
    src/camera/Camera.cpp
    src/camera/OrthographicCamera.cpp
    src/utils/FileManager.cpp
    src/utils/Logger.cpp
    src/utils/OBJLoader.cpp
    src/utils/Timer.cpp
    src/utils/TextureLoader.cpp
    src/maths/Noise.cpp
    src/input/Input.cpp
    src/objects/Model3D.cpp
    src/graphics/Mesh.cpp
    src/graphics/SkyBox.cpp
    src/graphics/primitives/IndexBuffer.cpp
    src/graphics/primitives/VertexFomat.cpp
    src/graphics/primitives/VertexArray.cpp
    src/graphics/primitives/VertexBuffer.cpp
    src/graphics/Shader.cpp
    src/graphics/renderer/RenderQueue.cpp
    src/graphics/renderer/Renderer.cpp
    src/graphics/texture/TextureCube.cpp
    src/graphics/texture/Texture2D.cpp
    src/graphics/texture/Texture.cpp
    src/core/Application.cpp
    src/core/Window.cpp
    src/core/ResourceSet.cpp
    src/vendor/stb_image/stb_image.cpp
    src/vendor/ImGui/main.cpp
    src/vendor/ImGui/imgui.cpp
    src/vendor/ImGui/imgui_impl_glfw_gl3.cpp
    src/vendor/ImGui/imgui_draw.cpp
    src/vendor/ImGui/imgui_demo.cpp
)

target_include_directories(game-framework-graphics PRIVATE
    include/
    include/Vendor/ImGui/
)

# temp - only for testing initial cmake setup
#SET(APP_EXE StaticTest)
#ADD_EXECUTABLE(${APP_EXE} test_static_lib.cpp)
#TARGET_LINK_LIBRARIES(${APP_EXE} game-framework-graphics)