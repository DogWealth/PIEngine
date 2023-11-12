#include "pipch.h"
#include "WindowsWindow.h"
#include "PIEngine/Events/ApplicationEvent.h"
#include "PIEngine/Events/KeyEvent.h"
#include "PIEngine/Events/MouseEvent.h"

namespace PIEngine {
	static bool s_GLFWInitialized = false;

	//�ص�������Ҫ�Ǿ�̬��Ա���������ûʵ����һ������Ҳû�취�����ĺ�����Ϊ�ص�����
	static void GLFWErrorCallback(int error, const char* decription)
	{
		PI_CORE_ERROR("GLFW Error ({0}): {1}", error, decription);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;


		PI_CORE_INFO("Creating window {0} ({1}, {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int sucess = glfwInit();//�����������κ�GLFW����֮ǰ�����ã���Ϊ�������ʼ������GLFW�⡣����ɹ��Ļ����ýӿڽ�����GL_TRUE������ͻ᷵��GL_FALSE��
			PI_CORE_ASSERT(sucess, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);

		m_Context = new OpenGLContext(m_Window);
		m_Context->Init();

		
		glfwSetWindowUserPointer(m_Window, &m_Data);//���Զ����ָ�����ݹ�����ָ��������
		SetVSync(true);

		//����GLFW�ص�
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);

				//PI_CORE_INFO(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}

				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}

				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, 1);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		//���������ַ�ʽ�����������¼�����ѯ��polling���͵ȴ���waiting����������ӽ���ʹ���¼���ѯ����ֻ�ᴦ���Ѿ����յ����¼����һ��������ء�
		glfwPollEvents();
		m_Context->SwapBuffers();
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//�������ָʾ��ֱ������������ǰ��Ҫ�ȴ�����֡��ͨ�������Ϊ��ֱͬ����Ĭ������£��������Ϊ0����ζ�Ż�����������������������һЩ���ٵĻ����ϣ���Ϊ��Ļ�����Ե��͵�60-75��ÿ����ٶȸ��£����֡����Զ����������������˷����CPU��GPU���ڡ����ң���Ϊ���������ܻ�����Ļ���µ���;�����������»���˺�ѡ���ˣ�Ӧ����Ҫ�����Ե����ý������Ϊ1��Ҳ�������óɸ��ߵ�ֵ������ͨ��������ⲻ�ᱻ�Ƽ�����Ϊ��ᵼ�������ӳ١�
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}