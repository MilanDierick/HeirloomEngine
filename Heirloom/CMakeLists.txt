cmake_minimum_required(VERSION 3.21)
project(Heirloom)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_C_FLAGS "-Wall -std=c99")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O4 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_CXX_FLAGS "-Wall -std=c++20")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

add_subdirectory(thirdparty/spdlog)
add_subdirectory(thirdparty/glfw)
add_subdirectory(thirdparty/glm)

add_library(Heirloom
        include/Heirloom.h
        src/hlpch.cpp
        src/hlpch.h
        thirdparty/stb_image/stb_image.cpp
        thirdparty/stb_image/stb_image.h
        thirdparty/imgui/imconfig.h
        thirdparty/imgui/imgui.h
        thirdparty/imgui/imgui_internal.h
        thirdparty/imgui/imstb_rectpack.h
        thirdparty/imgui/imstb_textedit.h
        thirdparty/imgui/imstb_truetype.h
        thirdparty/imgui/imgui.cpp
        thirdparty/imgui/imgui_demo.cpp
        thirdparty/imgui/imgui_draw.cpp
        thirdparty/imgui/imgui_tables.cpp
        thirdparty/imgui/imgui_widgets.cpp
        thirdparty/imgui/
        thirdparty/imgui/backends/imgui_impl_glfw.cpp
        thirdparty/imgui/backends/imgui_impl_opengl3.cpp
        thirdparty/glad/src/glad.c
        src/Heirloom/Core/Log.cpp
        src/Heirloom/Core/Log.h
        src/Heirloom/Profiler/Instrumentation.cpp
        src/Heirloom/Profiler/Instrumentation.h
        src/Heirloom/Core/EntryPoint.h
        src/Heirloom/Core/Application.cpp
        src/Heirloom/Core/Application.h
        src/Heirloom/Core/Core.h
        src/Heirloom/Core/Layer.cpp
        src/Heirloom/Core/Layer.h
        src/Heirloom/Core/Timestep.h
        src/Heirloom/Core/LayerStack.cpp
        src/Heirloom/Core/LayerStack.h
        src/Heirloom/Core/Window.h
        src/Heirloom/Events/ApplicationEventArgs.h
        src/Heirloom/Events/Event.h
        src/Heirloom/ImGui/ImGuiLayer.cpp
        src/Heirloom/ImGui/ImGuiLayer.h
        src/Heirloom/Events/KeyEventArgs.h
        src/Heirloom/Events/MouseEventArgs.h
        src/Heirloom/Core/Input.h
        src/Heirloom/Core/KeyCodes.h
        src/Heirloom/Core/LockFreeStack.h
        src/Heirloom/Core/MouseCodes.h
        src/Heirloom/Gameplay/Components/Component.h
        src/Heirloom/Gameplay/Components/SpriteRenderer.cpp
        src/Heirloom/Gameplay/Components/SpriteRenderer.h
        src/Heirloom/Gameplay/GameObject.cpp
        src/Heirloom/Gameplay/GameObject.h
        src/Heirloom/Gameplay/Transform.cpp
        src/Heirloom/Gameplay/Transform.h
        src/Heirloom/ImGui/ImGuiBuild.cpp
        src/Heirloom/Renderer/Buffer.cpp
        src/Heirloom/Renderer/Buffer.h
        src/Heirloom/Renderer/FrameBuffer.cpp
        src/Heirloom/Renderer/FrameBuffer.h
        src/Heirloom/Renderer/GraphicsContext.h
        src/Heirloom/Renderer/OrthographicCamera.cpp
        src/Heirloom/Renderer/OrthographicCamera.h
        src/Heirloom/Renderer/OrthographicCameraController.cpp
        src/Heirloom/Renderer/OrthographicCameraController.h
        src/Heirloom/Renderer/RenderCommand.cpp
        src/Heirloom/Renderer/RenderCommand.h
        src/Heirloom/Renderer/Renderer.cpp
        src/Heirloom/Renderer/Renderer.h
        src/Heirloom/Renderer/Renderer2D.cpp
        src/Heirloom/Renderer/Renderer2D.h
        src/Heirloom/Renderer/RendererAPI.cpp
        src/Heirloom/Renderer/RendererAPI.h
        src/Heirloom/Renderer/Shader.cpp
        src/Heirloom/Renderer/Shader.h
        src/Heirloom/Renderer/Sprite.h
        src/Heirloom/Renderer/Texture.cpp
        src/Heirloom/Renderer/Texture.h
        src/Heirloom/Renderer/VertexArray.cpp
        src/Heirloom/Renderer/VertexArray.h
        src/Platform/OpenGL/OpenGLBuffer.cpp
        src/Platform/OpenGL/OpenGLBuffer.h
        src/Platform/OpenGL/OpenGLContext.cpp
        src/Platform/OpenGL/OpenGLContext.h
        src/Platform/OpenGL/OpenGLFrameBuffer.cpp
        src/Platform/OpenGL/OpenGLFrameBuffer.h
        src/Platform/OpenGL/OpenGLRendererAPI.cpp
        src/Platform/OpenGL/OpenGLRendererAPI.h
        src/Platform/OpenGL/OpenGLShader.cpp
        src/Platform/OpenGL/OpenGLShader.h
        src/Platform/OpenGL/OpenGLTexture.cpp
        src/Platform/OpenGL/OpenGLTexture.h
        src/Platform/OpenGL/OpenGLVertexArray.cpp
        src/Platform/OpenGL/OpenGLVertexArray.h
        src/Platform/Windows/WindowsInput.cpp
        src/Platform/Windows/WindowsWindow.cpp
        src/Platform/Windows/WindowsWindow.h
        )

target_compile_definitions(Heirloom PRIVATE
        HL_DEBUG
        HL_PROFILE
        )

target_include_directories(Heirloom PRIVATE
        src
        thirdparty/spdlog/include
        thirdparty/stb_image
        thirdparty/glad/include
        thirdparty/imgui
        thirdparty/imgui/backends
        thirdparty/imgui/examples
        )

#target_precompile_headers(Heirloom PRIVATE
#        src/hlpch.cpp
#        src/hlpch.h
#        )

target_link_libraries(Heirloom PRIVATE
        spdlog
        glfw
        glm
        ${CMAKE_DL_LIBS}
        )