#include "pipch.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace PIEngine {
	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}