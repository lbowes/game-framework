set(GRAPHICS_SRC
    src/factorial.cpp
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
)

add_library(game-framework-graphics STATIC ${GRAPHICS_SRC})
target_include_directories(game-framework-graphics PRIVATE include/)

set(GRAPHICS_HEADERS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Tests
add_subdirectory(test)