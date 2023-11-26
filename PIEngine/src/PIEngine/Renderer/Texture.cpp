#include "pipch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace PIEngine {
	Ref<Texture2D> Texture2D::Creat(const std::string& path)
	{
		switch (Renderer::GetAPI())
		{
			case RendererAPI::API::None:
				PI_CORE_ASSERT(false, "RendererAPI::None is currently not supported!");
			case RendererAPI::API::OpenGL:
				return std::make_shared<OpenGLTexture2D>(path);
		}

		PI_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}
