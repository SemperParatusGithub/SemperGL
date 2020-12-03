#pragma once


#include <iostream>
#include <sstream>

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"
#include "Util/Vectors.h"

namespace SemperGL
{

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	class Event
	{
	public:
		virtual ~Event() = default;

		bool Handled = false;

		template<typename T>
		bool isType() const { return GetType() == T::GetStaticType(); }

		virtual int GetRepeatCount() const { return 0; }
		virtual KeyCode GetKeyCode() const { return Key(0); }

		virtual Vec2f GetMousePosition() const { return { 0.0f, 0.0f }; }
		virtual Vec2f GetOffset() const { return { 0.0f, 0.0f }; }
		virtual MouseCode GetMouseButton() const { return Mouse(0); }

		virtual unsigned int GetWidth() const { return 0; }
		virtual unsigned int GetHeight() const { return 0; }

		virtual EventType GetType() const = 0;
		virtual std::string GetName() const = 0;
	};

	namespace Events
	{
		template<typename T>
		static bool isType(Event &e)
		{
			return e.GetType() == T::GetStaticType();
		}
	}

	template<typename T>
	static bool isEvent(Event &e) { return e.GetType() == T::GetStaticType(); }

	class EventDispatcher
	{
	public:
		EventDispatcher(Event &event)
			: m_Event(event)
		{
		}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F &func)
		{
			if (m_Event.GetType() == T::GetStaticType())
			{
				m_Event.Handled = func(static_cast<T &>(m_Event));
				return true;
			}
			return false;
		}
	private:
		Event &m_Event;
	};

}