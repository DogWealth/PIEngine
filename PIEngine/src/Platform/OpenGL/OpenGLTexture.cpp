#include "pipch.h"
#include "OpenGLTexture.h"

#include "stb_image.h"

#include <glad/glad.h>

namespace PIEngine {
	OpenGLTexture2D::OpenGLTexture2D(const std::string& path)
		:m_Path(path)
	{
		//unsigned char ptr
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PI_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		//如果图片是RGBA，但你存储方式用的RGB，那么A通道会被当做R或者其他通道，造成混乱
		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		PI_CORE_ASSERT(internalFormat && dataFormat, "Format not supported!");

		/*glTexStorage* 为指定的纹理创建固定存储。也就是分配的存储空间不可改变，这样就可以让纹理对象停止跟踪纹理的某些方面。 而纹理中的内容可以使用glTexSubImage* 来改变。glTexStorage2D申请的纹理空间，可在后续glTexSubImage2D分割多个使用*/
		glCreateTextures(GL_TEXTURE_2D, 1, &m_RendererID);
		glTextureStorage2D(m_RendererID, 1, internalFormat, m_Width, m_Height);

		glTextureParameteri(m_RendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_RendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		glTextureSubImage2D(m_RendererID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);

		//数据放到gpu上后，可以删除内存上的数据
		stbi_image_free(data);

	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_RendererID);
	}

	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_RendererID);
	}

}