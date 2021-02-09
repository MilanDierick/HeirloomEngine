#include "hlpch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

Heirloom::RendererAPI* Heirloom::RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
