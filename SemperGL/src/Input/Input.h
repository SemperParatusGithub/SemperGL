#pragma once
#include "KeyCodes.h"
#include "MouseCodes.h"

#include "Util/Vectors.h"

struct GLFWwindow;

namespace SemperGL
{

	class Input
	{
	public:
		static void Init(GLFWwindow *windowHandle);

		static bool IsKeyPressed(KeyCode key);
		static bool IsMouseButtonPressed(MouseCode button);

		static Vec2f GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();	
	};
}