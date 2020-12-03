#pragma once

#include "Event.h"

namespace SemperGL
{

	class WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_Width(width), m_Height(height) {}

		virtual unsigned int GetWidth() const override { return m_Width; }
		virtual unsigned int GetHeight() const override { return m_Height; }

		std::string GetName() const override
		{
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
			return ss.str();
		}
		EventType GetType() const override
		{
			return GetStaticType();
		}
		static EventType GetStaticType()
		{
			return EventType::WindowResize;
		}

	private:
		unsigned int m_Width, m_Height;
	};

	class WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() = default;

		std::string GetName() const override
		{
			return { "WindowCloseEvent" };
		}
		EventType GetType() const override
		{
			return GetStaticType();
		}
		static EventType GetStaticType()
		{
			return EventType::WindowClose;
		}
	};

}
