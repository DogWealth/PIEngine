#pragma once
#include "PIEngine/Renderer/GraphicsContext.h"
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace PIEngine {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual void Init()			override;
		virtual void SwapBuffers()	override;

	private:
		GLFWwindow* m_WindowHandle;
	};
}