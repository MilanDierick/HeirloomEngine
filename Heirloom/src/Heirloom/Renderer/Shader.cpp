#include "hlpch.h"
#include "Shader.h"

#include <glad/glad.h>

// https://www.khronos.org/opengl/wiki/Shader_Compilation
Heirloom::Shader::Shader(const std::string& vertexSource, const std::string& fragmentSource): m_RendererID(0)
{
	// Create an empty vertex shader handle
	const GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

	// Send the vertex shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	const GLchar* source = static_cast<const GLchar*>(vertexSource.c_str());
	glShaderSource(vertexShader, 1, &source, nullptr);

	// Compile the vertex shader
	glCompileShader(vertexShader);

	GLint isCompiled = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(vertexShader);

		// TODO: Test this!
		HL_CORE_ERROR("{0}", infoLog.data());
		HL_CORE_ASSERT(false, "Vertex shader compilation failure!");

		return;
	}

	// Create an empty fragment shader handle
	const GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	// Send the fragment shader source code to GL
	// Note that std::string's .c_str is NULL character terminated.
	source = static_cast<const GLchar*>(fragmentSource.c_str());
	glShaderSource(fragmentShader, 1, &source, nullptr);

	// Compile the fragment shader
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
	if (isCompiled == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

		// We don't need the shader anymore.
		glDeleteShader(fragmentShader);
		// Either of them. Don't leak shaders.
		glDeleteShader(vertexShader);

		// TODO: Test this!
		HL_CORE_ERROR("{0}", infoLog.data());
		HL_CORE_ASSERT(false, "Fragment shader compilation failure!");

		return;
	}

	// Vertex and fragment shaders are successfully compiled.
	// Now time to link them together into a program.
	// Get a program object.
	m_RendererID = glCreateProgram();

	// Attach our shaders to our program
	glAttachShader(m_RendererID, vertexShader);
	glAttachShader(m_RendererID, fragmentShader);

	// Link our program
	glLinkProgram(m_RendererID);

	// Note the different functions here: glGetProgram* instead of glGetShader*.
	GLint isLinked = 0;
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, static_cast<int*>(&isLinked));
	if (isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(m_RendererID, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(m_RendererID, maxLength, &maxLength, &infoLog[0]);

		// We don't need the program anymore.
		glDeleteProgram(m_RendererID);
		// Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		// TODO: Test this!
		HL_CORE_ERROR("{0}", infoLog.data());
		HL_CORE_ASSERT(false, "Shader link failure!");

		return;
	}

	// Always detach shaders after a successful link.
	glDetachShader(m_RendererID, vertexShader);
	glDetachShader(m_RendererID, fragmentShader);
}

Heirloom::Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Heirloom::Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Heirloom::Shader::Unbind() const
{
	glUseProgram(0);
}
