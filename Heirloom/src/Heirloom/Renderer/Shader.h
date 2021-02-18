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

		virtual const std::string& GetName() = 0;

		static Ref<Shader> Create(const std::string& filePath);
		static Ref<Shader> Create(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
	};

	class ShaderLibrary
	{
	public:
		void Add(const std::string& name, Ref<Shader> shader);
		void Add(Ref<Shader> shader);
		Ref<Shader> Load(const std::string& filePath);
		Ref<Shader> Load(const std::string& name, const std::string& filePath);

		Ref<Shader> Get(const std::string& name);

		bool Exists(const std::string& name);
	
	private:
		std::unordered_map<std::string, Ref<Shader>> m_Shaders;
	};
}
