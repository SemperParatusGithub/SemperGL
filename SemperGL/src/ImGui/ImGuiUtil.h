#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

struct GLFWwindow;

namespace SemperGL
{
	class ImGuiUtil
	{
	public:
		static void Init(GLFWwindow *windowHandle);
		static void Shutdown();

		static void BeginFrame();
		static void EndFrame();
	};
}