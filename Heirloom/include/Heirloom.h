﻿#pragma once

// ==== Core ======================================================
#include "Heirloom/Core/Application.h"
#include "Heirloom/Core/Core.h"
#include "Heirloom/Core/Input.h"
#include "Heirloom/Core/KeyCodes.h"
#include "Heirloom/Core/Layer.h"
#include "Heirloom/Core/Log.h"
#include "Heirloom/Core/MouseButtonCodes.h"
#include "Heirloom/Core/Timestep.h"
#include "Heirloom/ImGui/ImGuiLayer.h"
// =================================================================

// ==== Gameplay ===================================================
#include "Heirloom/Gameplay/GameObject.h"
#include "Heirloom/Gameplay/Components/SpriteRenderer.h"
// =================================================================

// ==== Renderer ===================================================
#include "Heirloom/Renderer/OrthographicCamera.h"
#include "Heirloom/Renderer/OrthographicCameraController.h"
#include "Heirloom/Renderer/Renderer.h"
#include "Heirloom/Renderer/Renderer2D.h"
#include "Heirloom/Renderer/Texture.h"
#include "Heirloom/Renderer/FrameBuffer.h"
// =================================================================

#include "Heirloom/Audio/SimpleSoundEngine.h"
#include "Heirloom/Profiler/Instrumentation.h"

#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/transform.hpp"

#include "imgui/imgui.h"
