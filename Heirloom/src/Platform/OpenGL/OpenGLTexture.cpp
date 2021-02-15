#include "hlpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include "glad/glad.h"

Heirloom::OpenGLTexture2D::OpenGLTexture2D(const std::string& path): m_Path(path)
{
	GLenum pixelFormat { GL_RGB };
	int width, height, channels;
	stbi_set_flip_vertically_on_load(1);
	stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	HL_CORE_ASSERT(data, "Failed to load image!");
	m_Width = width;
	m_Height = height;

	// Create the actual texture on the GPU
	glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
	glTextureStorage2D(m_RendererID, 1, GL_RGB8, m_Width, m_Height);

	// Configure some parameters for the texture
	glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// Determine the pixel format
	switch (channels)
	{
		case 3:
			pixelFormat = GL_RGB;
			break;
		case 4:
			pixelFormat = GL_RGBA;
			break;
		default:
			HL_CORE_ERROR("Failed to create OpenGLTexture2D, unknown pixel format, bytes per pixel: {0}", channels * sizeof byte);
	}
	
	// Upload the texture to the GPU
	glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, pixelFormat, GL_UNSIGNED_BYTE, data);

	// Clean up our texture data
	stbi_image_free(data);
}

Heirloom::OpenGLTexture2D::~OpenGLTexture2D()
{
	glDeleteTextures(1, &m_RendererID);
}


void Heirloom::OpenGLTexture2D::Bind(const uint32_t slot)
{
	glBindTextureUnit(slot, m_RendererID);
}
