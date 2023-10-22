#include "pipch.h"
#include "WindowsWindow.h"
#include "PIEngine/Events/ApplicationEvent.h"
#include "PIEngine/Events/KeyEvent.h"
#include "PIEngine/Events/MouseEvent.h"

namespace PIEngine {
	static bool s_GLFWInitialized = false;

	//回调函数需要是静态成员函数，如果没实例化一个对象，也没办法让他的函数作为回调函数
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
			int sucess = glfwInit();//必须在其他任何GLFW函数之前被调用，因为它负责初始化整个GLFW库。如果成功的话，该接口将返回GL_TRUE，否则就会返回GL_FALSE。
			PI_CORE_ASSERT(sucess, "Could not intialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);//设置参数window中的窗口所关联的OpenGL环境为当前环境
		glfwSetWindowUserPointer(m_Window, &m_Data);//将自定义的指针数据关联到指定窗口上
		SetVSync(true);

		//设置GLFW回调
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
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
		//GLFW默认使用了双缓冲技术。这意味着每个窗口会有两个渲染缓冲区，一个前置缓冲区和一个后置缓冲区。前置缓冲区会在屏幕上显示而后置缓冲区是你渲染的目标。
		//当整个帧已经渲染完毕时，两个缓冲区需要进行交换，所以后置缓冲区会变成前置缓冲区，反之亦然。

		//GLFW需要定期地与窗口系统进行交流，不仅是为了接收事件，还是为了让整个应用看起来没有卡住。当你有着可见的窗口时，事件处理必须定期执行，正常情况下它会在每帧的缓冲区交换之后进行。

		//这里有两种方式来处理挂起的事件。轮询（polling）和等待（waiting）。这个例子将会使用事件轮询，它只会处理已经接收到的事件并且会立即返回。
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		//交换间隔指示了直到交换缓冲区前需要等待多少帧，通常被理解为垂直同步。默认情况下，交换间隔为0，意味着缓冲区交换会立即发生。在一些快速的机器上，因为屏幕保持以典型的60-75次每秒的速度更新，许多帧会永远看不到，所以这会浪费许多CPU和GPU周期。而且，因为缓冲区可能会在屏幕更新的中途被交换，导致画面撕裂。因此，应用需要代表性地设置交换间隔为1。也可以设置成更高的值，但是通常情况下这不会被推荐，因为这会导致输入延迟。
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