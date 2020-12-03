#pragma once

#include <iostream>
#include <assert.h>
#include <functional>
#include <glm/glm.hpp>

#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

#include "WindowIcon.h"

struct GLFWwindow;

namespace SemperGL
{
	class Window
	{
	public:
		Window(std::string title, uint32_t width, uint32_t height);
		~Window();

		void SetEventCallback(const std::function<void(Event &)> &callback);
		inline GLFWwindow *GetID() const { return m_Window; }

		void OnUpdate();
		void Clear(const glm::vec4 &clearColor = glm::vec4 { 0.7f, 0.7f, 0.7f, 0.7f });
		bool IsOpen() const;
		void Close();

		void SetIcon(const WindowIcon &icon);
		void SetTitle(const std::string &title);

		void SetVsync(bool vSync);
		void SetFullscreen();

		void SetPosition(const glm::vec2 &position);
		void SetSize(int x, int y);

		glm::vec2 GetPosition() const;
		glm::vec2 GetSize() const;

		void SetViewport(int x, int y, int width, int height);
		void SetMinimumSize(int minWidth, int minHeight);

		inline int GetWidth() const { return m_Data.width; }
		inline int GetHeight() const { return m_Data.height; }

	private:
		void SetGLFWCallbacks();

	private:
		GLFWwindow *m_Window;

		struct WindowData
		{
			std::string title;
			unsigned int width, height;
			std::function<void(Event &)> eventCallback;
		};
		WindowData m_Data;
	};
}