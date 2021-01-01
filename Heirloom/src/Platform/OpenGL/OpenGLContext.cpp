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
}

void Heirloom::OpenGLContext::SwapBuffers()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);
	glVertex2f(1.0f, -1.0f);
	glEnd();
	
	glfwSwapBuffers(m_WindowHandle);
}
