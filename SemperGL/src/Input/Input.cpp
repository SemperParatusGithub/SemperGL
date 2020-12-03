#include "Input.h"
#include <GLFW/glfw3.h>


namespace SemperGL
{
	namespace priv
	{
		static GLFWwindow *s_Window;
	}

	void Input::Init(GLFWwindow *window)
	{
		priv::s_Window = window;
	}

	bool Input::IsKeyPressed(KeyCode key)
	{
		auto state = glfwGetKey(priv::s_Window, static_cast<int32_t>(key));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(MouseCode button)
	{
		auto state = glfwGetMouseButton(priv::s_Window, static_cast<int32_t>(button));
		return state == GLFW_PRESS;
	}

	Vec2f Input::GetMousePosition()
	{
		double xpos, ypos;
		glfwGetCursorPos(priv::s_Window, &xpos, &ypos);

		return { (float)xpos, (float)ypos };
	}

	float Input::GetMouseX()
	{
		return GetMousePosition().x;
	}

	float Input::GetMouseY()
	{
		return GetMousePosition().y;
	}
}