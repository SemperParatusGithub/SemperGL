#include "Level.h"


enum State
{
	MainMenu = 0, Playing, Dead, Close
};

int main()
{
	sgl::Core::Init();

	sgl::Window window("Ship Game", 1280, 720);
	window.SetIcon(sgl::WindowIcon("res/icons/Icon.png"));
	window.SetVsync(1);
	bool fullscreen = false;
	window.SetEventCallback([&](sgl::Event &e)
		{
			if (e.isType<sgl::KeyPressedEvent>() && e.GetKeyCode() == sgl::Key::F11)
			{
				if (!fullscreen) {
					fullscreen = true;
					window.SetFullscreen();
					window.SetViewport(0, 0, window.GetWidth(), window.GetHeight());
				}
				else {
					window.SetSize(1280, 720);
					window.SetPosition({ 200.0f, 200.0f });
					window.SetViewport(0, 0, 1280, 720);
					fullscreen = false;
				}
			}
		});

	ImGuiIO io = ImGui::GetIO();
	ImFont *font = io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Bold.ttf", 120.0f);

	State GameState = MainMenu;
	sgl::Clock clock;

	// Player
	Player player;
	bool respawnt = false;

	// Level
	Level level;
	level.Reset();

	// Textures
	sgl::Texture backgroundTex("res/textures/Background.jpg");

	// Game Loop
	while (window.IsOpen())
	{
		auto deltaTime = clock.Restart();
	
		sgl::ImGuiUtil::BeginFrame();
		window.OnUpdate();

		if (GameState == MainMenu)
		{
			if (sgl::Input::IsKeyPressed(sgl::Key::Space) || sgl::Input::IsMouseButtonPressed(sgl::Mouse::Button0))
				GameState = Playing;

			if (respawnt)
			{
				sgl::Clock::Sleep(500);
				respawnt = false;
			}

			window.Clear();

			auto pos = ImGui::GetWindowPos();
			pos.x += window.GetWidth() * 0.5f - 300.0f;
			pos.y += window.GetHeight() * 0.6f;
			std::string highScore = std::string("Highscore: ") + std::to_string(player.GetHighscore());
			ImGui::GetForegroundDrawList()->AddText(font, 120.0f, pos, 0xffffffff, "Click to Play!");
			ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, highScore.c_str());

			sgl::Renderer2D::BeginScene(0, 0, 1280, 720);
			sgl::Renderer2D::DrawQuad({ 640.0f, 360.0f, 0.0f }, { 1280.0f, 720.0f }, backgroundTex);
			player.OnRender();
			sgl::Renderer2D::EndScene();
		}
		else if (GameState == Playing)
		{
			// Update
			player.OnUpdate(deltaTime);
			level.OnUpdate(deltaTime, player.GetHorizontalVelocity());

			if (level.CheckForCollision(player))
				GameState = Dead;

			window.Clear();

			// Render Score
			std::string score = std::string("Score: ") + std::to_string(player.GetScore());
			ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, score.c_str());

			sgl::Renderer2D::BeginScene(0, 0, 1280, 720);
			sgl::Renderer2D::DrawQuad( { 640.0f, 360.0f, 0.0f }, { 1280.0f, 720.0f }, backgroundTex);
			level.OnRender();
			player.OnRender();
			sgl::Renderer2D::EndScene();
		}
		else if (GameState == Dead)
		{
			if (player.GetScore() > player.GetHighscore())
				player.SetHighscore(player.GetScore());
			player = Player();
			level = Level();
			respawnt = true;
			GameState = MainMenu;
		}
		else if (GameState == Close)
		{
			window.Close();
		}
		sgl::ImGuiUtil::EndFrame();
	}
}