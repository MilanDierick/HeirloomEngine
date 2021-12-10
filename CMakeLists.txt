cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(Heirloom)

project(Sandbox)

add_executable(Sandbox Sandbox/src/Sandbox2D.cpp Sandbox/src/Sandbox2D.h Sandbox/src/SandboxApp.cpp)

target_include_directories(Sandbox PRIVATE
        Heirloom/include
        Heirloom/src
        Heirloom/thirdparty/spdlog/include
        Heirloom/thirdparty/imgui
        Heirloom/thirdparty/glm
        )

target_link_libraries(Sandbox PRIVATE
        Heirloom
        )

add_custom_command(
        TARGET Sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Sandbox/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)

project(Editor)

add_executable(Editor
        HeirloomEditor/src/EditorLayer.cpp
        HeirloomEditor/src/EditorLayer.h
        HeirloomEditor/src/HeirloomEditorApplication.cpp
        )

target_include_directories(Editor PRIVATE
        Heirloom/include
        Heirloom/src
        Heirloom/thirdparty/spdlog/include
        Heirloom/thirdparty/imgui
        Heirloom/thirdparty/glm
        )

target_link_libraries(Editor PRIVATE
        Heirloom
        )

add_custom_command(
        TARGET Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Sandbox/assets
        ${CMAKE_CURRENT_BINARY_DIR}/assets
)

add_custom_command(
        TARGET Editor POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
        ${CMAKE_SOURCE_DIR}/HeirloomEditor/imgui.ini
        ${CMAKE_CURRENT_BINARY_DIR}/
)