#include "hlpch.h"
#include "OpenGLShader.h"
#include <fstream>
#include <glm/gtc/type_ptr.hpp>
#include "glad/glad.h"
#include "Heirloom/Core/Application.h"

namespace Heirloom
{
	static GLenum ShaderTypeFromString(const std::string& type)
	{
		HL_PROFILE_FUNCTION()

		if (type == "vertex") return GL_VERTEX_SHADER;
		if (type == "fragment" || type == "pixel") return GL_FRAGMENT_SHADER;

		HL_CORE_ASSERT(false, "Unknown shader type!");
		return 0;
	}
}

Heirloom::OpenGLShader::OpenGLShader(const std::string& filePath)
{
	HL_PROFILE_FUNCTION()

	const std::string source                                    = ReadFile(filePath);
	const std::unordered_map<GLenum, std::string> shaderSources = PreProcess(source);
	Compile(shaderSources);

	// Extract name from filePath
	std::string::size_type lastSlash = filePath.find_last_of("/\\");
	lastSlash = lastSlash == std::string::npos ? 0 : lastSlash + 1;
	const std::string::size_type lastDot = filePath.rfind(".");
	const size_t count = lastDot == std::string::npos ? filePath.size() - lastSlash : lastDot - lastSlash;

	m_Name = filePath.substr(lastSlash, count);
}

Heirloom::OpenGLShader::OpenGLShader(const std::string& name,
									 const std::string& vertexSource,
									 const std::string& fragmentSource)
	: m_RendererID(0), m_Name(name)
{
	HL_PROFILE_FUNCTION()

	std::unordered_map<GLenum, std::string> sources;
	sources[GL_VERTEX_SHADER]   = vertexSource;
	sources[GL_FRAGMENT_SHADER] = fragmentSource;
	Compile(sources);
}

Heirloom::OpenGLShader::~OpenGLShader()
{
	HL_PROFILE_FUNCTION()

	glDeleteProgram(m_RendererID);
}

void Heirloom::OpenGLShader::Bind() const
{
	HL_PROFILE_FUNCTION()

	glUseProgram(m_RendererID);
}

void Heirloom::OpenGLShader::Unbind() const
{
	HL_PROFILE_FUNCTION()

	glUseProgram(0);
}

void Heirloom::OpenGLShader::SetInt(const std::string name, const int value)
{
	HL_PROFILE_FUNCTION()

	UploadUniformInt(name, value);
}

void Heirloom::OpenGLShader::SetFloat(const std::string name, const float value)
{
	HL_PROFILE_FUNCTION()

	UploadUniformFloat(name, value);
}

void Heirloom::OpenGLShader::SetFloat2(const std::string name, const glm::float2 value)
{
	HL_PROFILE_FUNCTION()

	UploadUniformFloat2(name, value);
}

void Heirloom::OpenGLShader::SetFloat3(const std::string name, const glm::float3 value)
{
	HL_PROFILE_FUNCTION()

	UploadUniformFloat3(name, value);
}

void Heirloom::OpenGLShader::SetFloat4(const std::string name, const glm::float4 value)
{
	HL_PROFILE_FUNCTION()

	UploadUniformFloat4(name, value);
}

void Heirloom::OpenGLShader::SetMat4(const std::string name, const glm::mat4 value)
{
	HL_PROFILE_FUNCTION()

	UploadUniformMat4(name, value);
}

void Heirloom::OpenGLShader::UploadUniformInt(const std::string& name, const int value) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1i(location, value);
}

void Heirloom::OpenGLShader::UploadUniformFloat(const std::string& name, const float value) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform1f(location, value);
}

void Heirloom::OpenGLShader::UploadUniformFloat2(const std::string& name, const glm::vec2 values) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform2f(location, values.x, values.y);
}

void Heirloom::OpenGLShader::UploadUniformFloat3(const std::string& name, const glm::vec3 values) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform3f(location, values.x, values.y, values.z);
}

void Heirloom::OpenGLShader::UploadUniformFloat4(const std::string& name, const glm::vec4 values) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniform4f(location, values.x, values.y, values.z, values.a);
}

void Heirloom::OpenGLShader::UploadUniformMat3(const std::string& name, glm::mat3 matrix) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix3fv(location, 1, GL_FALSE, value_ptr(matrix));
}

void Heirloom::OpenGLShader::UploadUniformMat4(const std::string& name, const glm::mat4 matrix) const
{
	HL_PROFILE_FUNCTION()

	const GLint location = glGetUniformLocation(m_RendererID, name.c_str());
	glUniformMatrix4fv(location, 1, GL_FALSE, value_ptr(matrix));
}

std::string Heirloom::OpenGLShader::ReadFile(const std::string& filePath)
{
	HL_PROFILE_FUNCTION()

	std::string result;
	std::ifstream in(filePath, std::ios::in | std::ios::binary);

	if (in)
	{
		in.seekg(0, std::ios::end);
		#pragma warning(disable : 4244)
		result.resize(in.tellg());
		#pragma warning(default : 4244)
		in.seekg(0, std::ios::beg);
		in.read(&result[0], result.size());
		in.close();
	}
	else
		HL_CORE_ERROR("Could not open file '{0}'", filePath);

	return result;
}

std::unordered_map<GLenum, std::string> Heirloom::OpenGLShader::PreProcess(const std::string& source)
{
	HL_PROFILE_FUNCTION()

	std::unordered_map<GLenum, std::string> shaderSources;

	const char* typeToken        = "#type";
	const size_t typeTokenLength = strlen(typeToken);
	size_t pos                   = source.find(typeToken, 0);
	while (pos != std::string::npos)
	{
		const size_t eol = source.find_first_of("\r\n", pos);
		HL_CORE_ASSERT(eol != std::string::npos, "Syntax error");
		const size_t begin = pos + typeTokenLength + 1;
		std::string type   = source.substr(begin, eol - begin);
		HL_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type specified");

		const size_t nextLinePos                  = source.find_first_not_of("\r\n", eol);
		pos                                       = source.find(typeToken, nextLinePos);
		shaderSources[ShaderTypeFromString(type)] = source.substr(nextLinePos,
																  pos - (nextLinePos == std::string::npos
																			 ? source.size() - 1
																			 : nextLinePos));
	}

	return shaderSources;
}

void Heirloom::OpenGLShader::Compile(const std::unordered_map<GLenum, std::string>& shaderSources)
{
	HL_PROFILE_FUNCTION()

	const GLuint program = glCreateProgram();
	HL_CORE_ASSERT(shaderSources.size() <= 2, "Only up to two shaders are supported!")
	std::array<GLenum, 2> glShaderIDs;
	int glShaderIDIndex = 0;

	for (const auto& [type, source] : shaderSources)
	{
		const GLuint shader = glCreateShader(type);

		const GLchar* sourceCStr = source.c_str();
		glShaderSource(shader, 1, &sourceCStr, nullptr);

		glCompileShader(shader);

		GLint isCompiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

			std::vector<GLchar> infoLog(maxLength);
			glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

			glDeleteShader(shader);

			HL_CORE_ERROR("{0}", infoLog.data());
			HL_CORE_ASSERT(false, "Shader compilation failure!");
			break;
		}

		glAttachShader(program, shader);
		glShaderIDs[glShaderIDIndex++] = shader;
	}

	m_RendererID = program;

	// Link our program
	glLinkProgram(program);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(program, GL_LINK_STATUS, static_cast<int*>(&isLinked));
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(program);

		for (auto id : glShaderIDs)
			glDeleteShader(id);

		HL_CORE_ERROR("{0}", infoLog.data());
		HL_CORE_ASSERT(false, "Shader link failure!");
		return;
	}

	for (auto id : glShaderIDs)
	{
		glDetachShader(program, id);
		glDeleteShader(id);
	}
}
