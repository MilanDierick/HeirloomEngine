// Author: Milan Dierick
// Created: 02/03/2021 7:24 PM
// Solution: HeirloomEngine

#pragma once
#include <glm/glm.hpp>
#include "Heirloom/Renderer/Shader.h"

// TODO: Remove this mess!
typedef unsigned int GLenum;

namespace Heirloom
{
	class OpenGLShader final : public Shader
	{
	public:
		explicit OpenGLShader(const std::string& filePath);
		OpenGLShader(const std::string& name, const std::string& vertexSource, const std::string& fragmentSource);
		~OpenGLShader() override;

		OpenGLShader(const OpenGLShader& other)                = delete;
		OpenGLShader(OpenGLShader&& other) noexcept            = delete;
		OpenGLShader& operator=(const OpenGLShader& other)     = delete;
		OpenGLShader& operator=(OpenGLShader&& other) noexcept = delete;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(std::string name, int value) override;
		void SetFloat(std::string name, float value) override;
		void SetFloat2(std::string name, glm::float2 value) override;
		void SetFloat3(std::string name, glm::float3 value) override;
		void SetFloat4(std::string name, glm::float4 value) override;
		void SetMat4(std::string name, glm::mat4 value) override;

		const std::string& GetName() override { return m_Name; }

		void UploadUniformInt(const std::string& name, int value) const;

		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, glm::vec2 values) const;
		void UploadUniformFloat3(const std::string& name, glm::vec3 values) const;
		void UploadUniformFloat4(const std::string& name, glm::vec4 values) const;

		void UploadUniformMat3(const std::string& name, glm::mat3 matrix) const;
		void UploadUniformMat4(const std::string& name, glm::mat4 matrix) const;

	private:
		std::string ReadFile(const std::string& filePath);
		std::unordered_map<GLenum, std::string> PreProcess(const std::string& source);
		void Compile(const std::unordered_map<GLenum, std::string>& shaderSources);

		uint32_t m_RendererID;
		std::string m_Name;
	};
}
