#include "hlpch.h"
#include "OpenGLContext.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"

Heirloom::OpenGLContext::OpenGLContext(GLFWwindow* const windowHandle): m_WindowHandle(windowHandle)
{
	HL_CORE_ASSERT(windowHandle, "Window handle is null!");
}

void Heirloom::OpenGLContext::Init()
{
	glfwMakeContextCurrent(m_WindowHandle);
	const int status = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
	HL_CORE_ASSERT(status, "Failed to initialize Glad!");

	HL_CORE_INFO("OpenGL Info:");
	HL_CORE_INFO("    Vendor: {0}", glGetString(GL_VENDOR));
	HL_CORE_INFO("    Renderer: {0}", glGetString(GL_RENDERER));
	HL_CORE_INFO("    Version: {0}", glGetString(GL_VERSION));
}

void Heirloom::OpenGLContext::SwapBuffers()
{
	glfwSwapBuffers(m_WindowHandle); 
}
