#pragma once

namespace Heirloom
{
	class Shader
	{
	public:
		Shader()          = default;
		virtual ~Shader() = default;

		Shader(const Shader& other)                = delete;
		Shader(Shader&& other) noexcept            = delete;
		Shader& operator=(const Shader& other)     = delete;
		Shader& operator=(Shader&& other) noexcept = delete;

		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}
