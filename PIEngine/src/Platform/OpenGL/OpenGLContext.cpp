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
		glfwMakeContextCurrent(m_WindowHandle);//���ò���window�еĴ�����������OpenGL����Ϊ��ǰ����
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PI_CORE_ASSERT(status, "Falied to initialize Glad!");

		PI_CORE_INFO("OpenGL Info: ");
		PI_CORE_INFO("Vendor: {0}", (const char*)glGetString(GL_VENDOR));
		PI_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
		PI_CORE_INFO("Version: {0}", (const char*)glGetString(GL_VERSION));
	}

	void OpenGLContext::SwapBuffers()
	{
		/*GLFWĬ��ʹ����˫���弼����
		����ζ��ÿ�����ڻ���������Ⱦ��������һ��ǰ�û�������һ�����û�������
		ǰ�û�����������Ļ����ʾ�����û�����������Ⱦ��Ŀ�ꡣ
		������֡�Ѿ���Ⱦ���ʱ��������������Ҫ���н��������Ժ��û���������ǰ�û���������֮��Ȼ��
		GLFW��Ҫ���ڵ��봰��ϵͳ���н�����������Ϊ�˽����¼�������Ϊ��������Ӧ�ÿ�����û�п�ס��
		�������ſɼ��Ĵ���ʱ���¼�������붨��ִ�У����������������ÿ֡�Ļ���������֮����С�*/

		glfwSwapBuffers(m_WindowHandle);
	}

}