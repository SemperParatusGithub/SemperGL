#include "Particles.h"


int main()
{
	sgl::Core::Init();

	sgl::Window window("Window", 1280, 720);
	window.SetVsync(false);
	sgl::Clock clock;

	ImFont *openSansRegular = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Regular.ttf", 30.0f);
	ImFont *openSansRegularOverlay = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Regular.ttf", 22.0f);
	ImFont *openSansBold = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Bold.ttf", 32.0f);
	ImGui::GetIO().FontDefault = openSansRegular;
	ImGui::GetStyle().WindowMinSize = ImVec2 { 600.0f, 550.0f };

	Particles particles(25000);
	EmissionSettings settings;
	float size[2] = { 50.0f, 50.0f };
	float startCol[4] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float endCol[4] = { 0.0f, 0.0f, 1.0f, 1.0f };

	bool showSettings = true;

	while (window.IsOpen())
	{
		sgl::ImGuiUtil::BeginFrame();

		auto deltaTime = clock.Restart();

		window.OnUpdate();
		particles.OnUpdate(deltaTime);

		if (sgl::Input::IsMouseButtonPressed(sgl::Mouse::Button0))
			particles.Emit(settings);

		ImGui::PushFont(openSansBold);
		ImGui::Begin("Settings");
		ImGui::PushFont(openSansRegular);
		ImGui::SliderInt("Emission Count", (int *) &settings.emmissionCount, 1, 1000);
		ImGui::SliderFloat("Lifetime (s)", &settings.lifetime, 0.0f, 10.0f);
		ImGui::SliderFloat("Speed", &settings.speed, 0.0f, 10.0f);
		ImGui::SliderFloat2("Size", size, 0.0f, 250.0f);
		ImGui::ColorEdit4("Start Color", &startCol[0]);
		ImGui::ColorEdit4("End Color", &endCol[0]);
		ImGui::PopFont();
		ImGui::End();
		ImGui::PopFont();

		auto stats = sgl::Renderer2D::GetStats();
		ImGui::Begin("Render Stats");
		ImGui::Text("Framerate: %.2f FPS", ImGui::GetIO().Framerate);
		ImGui::Text("Draw Calls: %d", stats.drawCalls);
		ImGui::Text("Quads: %d", stats.quads);
		ImGui::Text("Triangles: %d", stats.triangles);
		ImGui::Text("Vertices: %d", stats.vertices);
		ImGui::Text("Indices: %d", stats.indices);
		ImGui::End();
		sgl::Renderer2D::ResetStats();

		settings.size = { size[0], size[1] };
		settings.startColor = { startCol[0], startCol[1], startCol[2], startCol[3] };
		settings.endColor = { endCol[0], endCol[1], endCol[2], endCol[3] };
		settings.emitter = { sgl::Input::GetMouseX(), window.GetHeight() - sgl::Input::GetMouseY() };

		window.Clear();
		sgl::Renderer2D::BeginScene(0, 0, window.GetWidth(), window.GetHeight());
		particles.OnRender();
		sgl::Renderer2D::EndScene();

		sgl::ImGuiUtil::EndFrame();
	}

	return EXIT_SUCCESS;
}