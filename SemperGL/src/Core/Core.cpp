#include "Core.h"
#include "Util/Random.h"

#include <GLFW/glfw3.h>
#include <iostream>

#include <Windows.h>


namespace SemperGL
{
	void Core::Init()
	{
			Random::Init();

			int success = glfwInit();
			if (!success)
				std::cout << "Failed to initialize GLFW!" << std::endl;

#		ifdef SGL_DISTRIBUTE
			HWND hwnd = GetConsoleWindow();
			ShowWindow(hwnd, 0);
#		endif
		
	}
}
