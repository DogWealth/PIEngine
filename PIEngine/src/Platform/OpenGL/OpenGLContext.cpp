#include "pipch.h"
#include "OpenGLContext.h"

namespace PIEngine {
	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		PI_CORE_ASSERT(m_WindowHandle, "WindowHandle is null!");
	}

	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);//设置参数window中的窗口所关联的OpenGL环境为当前环境
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PI_CORE_ASSERT(status, "Falied to initialize Glad!");
	}

	void OpenGLContext::SwapBuffers()
	{
		/*GLFW默认使用了双缓冲技术。
		这意味着每个窗口会有两个渲染缓冲区，一个前置缓冲区和一个后置缓冲区。
		前置缓冲区会在屏幕上显示而后置缓冲区是你渲染的目标。
		当整个帧已经渲染完毕时，两个缓冲区需要进行交换，所以后置缓冲区会变成前置缓冲区，反之亦然。
		GLFW需要定期地与窗口系统进行交流，不仅是为了接收事件，还是为了让整个应用看起来没有卡住。
		当你有着可见的窗口时，事件处理必须定期执行，正常情况下它会在每帧的缓冲区交换之后进行。*/

		glfwSwapBuffers(m_WindowHandle);
	}

}