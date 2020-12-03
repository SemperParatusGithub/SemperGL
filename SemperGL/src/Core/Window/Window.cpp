#include "Window.h"

#include <glad/glad.h>

#include "Input/Input.h"
#include "ImGui/ImGuiUtil.h"

#include "Renderer/Renderer2D.h"


namespace SemperGL
{
	static uint8_t s_WindowCount = 0;

	static void GLFWErrorCallback(int error, const char *description)
	{
		std::cout << "GLFW Error " << error << ": " << description << std::endl;
	}
	static void DefaultEventCallback(Event &e)
	{
		if (e.isType<WindowResizeEvent>())
			glViewport(0, 0, e.GetWidth(), e.GetHeight());
	}

	Window::Window(std::string title, uint32_t width, uint32_t height)
	{
		SetEventCallback(DefaultEventCallback);

		m_Data.title = title;
		m_Data.width = width;
		m_Data.height = height;

		if (s_WindowCount >= 1)
			assert(false, "Only one Window supported");

		std::cout << "Creating Window (" << m_Data.width << ", " << m_Data.height << ")" << std::endl;

		m_Window = glfwCreateWindow((int)m_Data.width, (int)m_Data.height, m_Data.title.c_str(), nullptr, nullptr);
		s_WindowCount++;

		glfwMakeContextCurrent(m_Window);
		int status = gladLoadGLLoader((GLADloadproc) glfwGetProcAddress);
		assert(status);

		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

		ImGuiUtil::Init(m_Window);
		Input::Init(m_Window);
		Renderer2D::Init();

		// Set global OpenGL state
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glfwSetWindowUserPointer(m_Window, &m_Data);
		glfwSetErrorCallback(GLFWErrorCallback);
		SetGLFWCallbacks();
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		--s_WindowCount;

		if (s_WindowCount == 0)
		{
			Renderer2D::Shutdown();
			ImGuiUtil::Shutdown();
			glfwTerminate();
		}
	}

	void Window::SetEventCallback(const std::function<void(Event &)> &callback)
	{
		m_Data.eventCallback = callback;
	}
	void Window::OnUpdate()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}
	void Window::Clear(const glm::vec4 &clearColor)
	{
		glClearColor(clearColor.r, clearColor.g, clearColor.b, clearColor.a);
		glClear(GL_COLOR_BUFFER_BIT);
	}
	bool Window::IsOpen() const
	{
		return !glfwWindowShouldClose(m_Window);
	}

	void Window::Close()
	{
		glfwSetWindowShouldClose(m_Window, GLFW_TRUE);
	}

	void Window::SetIcon(const WindowIcon &icon)
	{
		glfwSetWindowIcon(m_Window, 1, (GLFWimage*)icon.GetIcon());
	}
	void Window::SetTitle(const std::string &title)
	{
		glfwSetWindowTitle(m_Window, title.c_str());
	}

	void Window::SetVsync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);
	}
	void Window::SetFullscreen()
	{
		glfwSetWindowSize(m_Window, glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height);
		glfwSetWindowPos(m_Window, 0, 0);
		SetViewport(0, 0, glfwGetVideoMode(glfwGetPrimaryMonitor())->width, glfwGetVideoMode(glfwGetPrimaryMonitor())->height);
	}

	void Window::SetPosition(const glm::vec2 &position)
	{
		glfwSetWindowPos(m_Window, (int) position.x, (int) position.y);
	}
	void Window::SetSize(int x, int y)
	{
		glfwSetWindowSize(m_Window, x, y);
	}

	glm::vec2 Window::GetPosition() const
	{
		int xPos, yPos;
		glfwGetWindowPos(m_Window, &xPos, &yPos);
		return { (float) xPos, (float) yPos };
	}
	glm::vec2 Window::GetSize() const
	{
		int sizeX, sizeY;
		glfwGetWindowSize(m_Window, &sizeX, &sizeY);
		return { (float) sizeX, (float) sizeY };
	}

	void Window::SetViewport(int x, int y, int width, int height)
	{
		glViewport(x, y, width, height);
	}
	void Window::SetMinimumSize(int minWidth, int minHeight)
	{
		glfwSetWindowSizeLimits(m_Window, minWidth, minHeight, GLFW_DONT_CARE, GLFW_DONT_CARE);
	}
	void Window::SetGLFWCallbacks()
	{
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow *window, int width, int height)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
				data.width = width;
				data.height = height;

				WindowResizeEvent event(width, height);
				data.eventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow *window)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.eventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 0);
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<KeyCode>(key));
					data.eventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<KeyCode>(key), 1);
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetCharCallback(m_Window, [](GLFWwindow *window, unsigned int keycode)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				KeyTypedEvent event(static_cast<KeyCode>(keycode));
				data.eventCallback(event);
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(static_cast<MouseCode>(button));
					data.eventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(static_cast<MouseCode>(button));
					data.eventCallback(event);
					break;
				}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow *window, double xOffset, double yOffset)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float) xOffset, (float) yOffset);
				data.eventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xPos, double yPos)
			{
				WindowData &data = *(WindowData *) glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float) xPos, (float) yPos);
				data.eventCallback(event);
			});
	}
}