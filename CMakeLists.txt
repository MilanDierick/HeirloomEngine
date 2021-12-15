cmake_minimum_required(VERSION 3.21)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(CMAKE_C_FLAGS "-Wall -std=c99 -m64")
set(CMAKE_C_FLAGS_DEBUG "-g")
set(CMAKE_C_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "-O2 -g")

set(CMAKE_CXX_FLAGS "-Wall -std=c++20 -m64")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O2 -g")

add_subdirectory(Heirloom)

project(Sandbox)

add_executable(Sandbox Sandbox/src/Sandbox2D.cpp Sandbox/src/Sandbox2D.h Sandbox/src/SandboxApp.cpp)

target_include_directories(Sandbox PRIVATE
        Heirloom/include
        Heirloom/src
        Heirloom/thirdparty/spdlog/include
        Heirloom/thirdparty/imgui
        Heirloom/thirdparty/glm
        Heirloom/thirdparty/entt/src
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
        Heirloom/thirdparty/entt/src
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

if (${CMAKE_BUILD_TYPE} STREQUAL Debug)
    target_compile_definitions(Sandbox PRIVATE HL_DEBUG HL_PROFILE)
    target_compile_definitions(Editor PRIVATE HL_DEBUG HL_PROFILE)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL Release)
    target_compile_definitions(Sandbox PRIVATE)
    target_compile_definitions(Editor PRIVATE)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
    target_compile_definitions(Sandbox PRIVATE HL_DEBUG HL_PROFILE)
    target_compile_definitions(Editor PRIVATE HL_DEBUG HL_PROFILE)
endif ()

if (${CMAKE_BUILD_TYPE} STREQUAL MinSizeRel)
    target_compile_definitions(Sandbox PRIVATE)
    target_compile_definitions(Editor PRIVATE)
endif ()