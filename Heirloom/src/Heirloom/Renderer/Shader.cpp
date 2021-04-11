#include "hlpch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Heirloom/Core/Application.h"
#include "Platform/OpenGL/OpenGLShader.h"

Heirloom::Ref<Heirloom::Shader> Heirloom::Shader::Create(const std::string& filePath)
{
	HL_PROFILE_FUNCTION()

	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(filePath);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

Heirloom::Ref<Heirloom::Shader> Heirloom::Shader::Create(const std::string& name,
														 const std::string& vertexSource,
														 const std::string& fragmentSource)
{
	HL_PROFILE_FUNCTION()

	switch (Renderer::GetAPI())
	{
		case RendererAPI::API::None: HL_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			return nullptr;
		case RendererAPI::API::OpenGL: return CreateRef<OpenGLShader>(name, vertexSource, fragmentSource);
	}

	HL_CORE_ASSERT(false, "Unknown RendererAPI!");
	return nullptr;
}

void Heirloom::ShaderLibrary::Add(const std::string& name, const Ref<Shader> shader)
{
	HL_PROFILE_FUNCTION()

	HL_CORE_ASSERT(!Exists(name), "Shader already exists!");
	m_Shaders[name] = shader;
}

void Heirloom::ShaderLibrary::Add(const Ref<Shader> shader)
{
	HL_PROFILE_FUNCTION()

	const std::string& name = shader->GetName();
	Add(name, shader);
}

Heirloom::Ref<Heirloom::Shader> Heirloom::ShaderLibrary::Load(const std::string& filePath)
{
	HL_PROFILE_FUNCTION()

	const Ref<Shader> shader = Shader::Create(filePath);
	Add(shader);
	return shader;
}

Heirloom::Ref<Heirloom::Shader> Heirloom::ShaderLibrary::Load(const std::string& name, const std::string& filePath)
{
	HL_PROFILE_FUNCTION()

	const Ref<Shader> shader = Shader::Create(filePath);
	Add(name, shader);
	return shader;
}

Heirloom::Ref<Heirloom::Shader> Heirloom::ShaderLibrary::Get(const std::string& name)
{
	HL_PROFILE_FUNCTION()

	HL_CORE_ASSERT(Exists(name), "Shader not found!");
	return m_Shaders[name];
}

bool Heirloom::ShaderLibrary::Exists(const std::string& name)
{
	HL_PROFILE_FUNCTION()

	return m_Shaders.find(name) != m_Shaders.end();
}
