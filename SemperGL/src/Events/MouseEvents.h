#pragma once

#include "Event.h"

namespace SemperGL
{

	class MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y)
			: m_MouseX(x), m_MouseY(y) {}

		virtual Vec2f GetMousePosition() const override { return { m_MouseX, m_MouseY }; }

		std::string GetName() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
		EventType GetType() const override
		{
			return GetStaticType();
		}
		static EventType GetStaticType()
		{
			return EventType::MouseMoved;
		}
	private:
		float m_MouseX, m_MouseY;
	};

	class MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset)
			: m_XOffset(xOffset), m_YOffset(yOffset) {}

		virtual Vec2f GetOffset() const override { return { m_XOffset, m_YOffset }; }

		std::string GetName() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: " << GetOffset().x << ", " << GetOffset().y;
			return ss.str();
		}
		EventType GetType() const override
		{
			return GetStaticType();
		}
		static EventType GetStaticType()
		{
			return EventType::MouseScrolled;
		}

	private:
		float m_XOffset, m_YOffset;
	};

	class MouseButtonEvent : public Event
	{
	public:
		virtual inline MouseCode GetMouseButton() const override { return m_Button; }

	protected:
		MouseButtonEvent(MouseCode button)
			: m_Button(button) {}

		MouseCode m_Button;
	};

	class MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		std::string GetName() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		EventType GetType() const override
		{
			return GetStaticType();
		}
		static EventType GetStaticType()
		{
			return EventType::MouseButtonPressed;
		}
	};

	class MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(MouseCode button)
			: MouseButtonEvent(button) {}

		std::string GetName() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << m_Button;
			return ss.str();
		}
		EventType GetType() const override
		{
			return GetStaticType();
		}
		static EventType GetStaticType()
		{
			return EventType::MouseButtonPressed;
		}
	};

}