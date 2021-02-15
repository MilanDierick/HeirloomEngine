#pragma once
#include <glm/fwd.hpp>

#include "Heirloom/Renderer/Shader.h"

namespace Heirloom
{
	class OpenGLShader final : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader();

		OpenGLShader(const OpenGLShader& other)                = delete;
		OpenGLShader(OpenGLShader&& other) noexcept            = delete;
		OpenGLShader& operator=(const OpenGLShader& other)     = delete;
		OpenGLShader& operator=(OpenGLShader&& other) noexcept = delete;

		void Bind() const override;
		void Unbind() const override;

		void UploadUniformInt(const std::string& name, int value) const;

		void UploadUniformFloat(const std::string& name, float value) const;
		void UploadUniformFloat2(const std::string& name, glm::vec2 values) const;
		void UploadUniformFloat3(const std::string& name, glm::vec3 values) const;
		void UploadUniformFloat4(const std::string& name, glm::vec4 values) const;

		void UploadUniformMat3(const std::string& name, glm::mat3 matrix) const;
		void UploadUniformMat4(const std::string& name, glm::mat4 matrix) const;
	
	private:
		uint32_t m_RendererID;
	};
}
