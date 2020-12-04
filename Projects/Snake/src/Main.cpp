#include <SemperGL/SemperGL.h>
#include <time.h>

unsigned int xFields = 35;
unsigned int yFields = 25;
unsigned int fieldSize = 32;

unsigned int width = fieldSize * xFields;
unsigned int height = fieldSize * yFields;


int main()
{
	sgl::Core::Init()
	std::srand(static_cast<unsigned int>(time(nullptr)));

	enum State { MainMenu = 0, Playing, Dead, Close } GameState = State::MainMenu;
	enum dir { w = 0, a, s, d } direction = dir::d;
	bool showSettings = false;

	sgl::Window window("Snake", width, height);
	window.SetVsync(true);
	window.SetMinimumSize(1280, 720);

	ImGuiIO io = ImGui::GetIO();
	ImFont *font = io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans-Regular.ttf", 120.0f);
	ImFont *font2 = io.Fonts->AddFontFromFileTTF("res/fonts/OpenSans-Regular.ttf", 32.0f);
	ImGui::GetStyle().WindowMinSize = ImVec2 { 600.0f, 850.0f };

	sgl::Clock clock;
	uint32_t score = 0, highscore = 0;

	sgl::Texture FrameTex("res/textures/Frame.png");

	std::vector<sgl::Vec2f> SnakePositions;
	for(std::size_t i = 0; i < 5; i++)
		SnakePositions.push_back({ -100.0f, -100.0f });

	glm::vec4 startColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	glm::vec4 endColor = { 0.0f, 0.0f, 1.0f, 1.0f };
	glm::vec4 clearColor = { 0.0f, 0.0f, 0.0f, 1.0f };
	float bgOpacity = 1.0f;

	sgl::Vec2f FruitPosition = { (std::rand() % (xFields-1)) * fieldSize, (std::rand() % (yFields-1)) * fieldSize };

	while (window.ShouldNotClose())
	{
		sgl::ImGuiNewFrame();
		window.OnUpdate();

		if (GameState == MainMenu)
		{
			auto pos = ImGui::GetWindowPos();
			pos.x += window.GetWidth() * 0.5f - 300.0f;
			pos.y += window.GetHeight() * 0.4f;
			std::string highScore = std::string("Highscore: ") + std::to_string(highscore);
			ImGui::GetForegroundDrawList()->AddText(font, 68.0f, pos, 0xffffffff, "Press Space to Play!");
			ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(),  0xffffffff, highScore.c_str());
	
			if (sgl::Input::IsKeyPressed(sgl::Key::Space))
				GameState = Playing;
			if (sgl::Input::IsKeyPressed(sgl::Key::Escape))
				GameState = Close;
			if (sgl::Input::IsKeyPressed(sgl::Key::F9))
				showSettings = true;

			sgl::Renderer::Clear(GL_COLOR_BUFFER_BIT);

			if (showSettings)
			{
				ImGui::PushFont(font2);
				if (!ImGui::Begin("Settings", &showSettings))
					ImGui::End();
				else
				{
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 1.29); ImGui::SliderInt("xFields ", (int *)&xFields, 5, 100);
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 1.29); ImGui::SliderInt("yFields ", (int *)&yFields, 5, 100);
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 1.29); ImGui::SliderInt("Field Size ", (int *)&fieldSize, 5, 100);
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 1.29); ImGui::SliderFloat("Opacity ", &bgOpacity, 0.0f, 1.0f);
					ImGui::Spacing();
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 3.50); ImGui::ColorPicker3("StartColor: ", &startColor[0]);
					ImGui::SameLine(ImGui::GetWindowSize().x / 2);
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 3.5); ImGui::ColorPicker3("EndColor: ", &endColor[0]);
					ImGui::Spacing();
					ImGui::SetNextItemWidth(ImGui::GetWindowSize().x / 3.5); ImGui::ColorPicker3("ClearColor: ", &clearColor[0]);
					ImGui::End();
				}
				ImGui::PopFont();
			}

			int width = fieldSize * xFields;
			int height = fieldSize * yFields;

			glfwSetWindowSize(window.GetID(), width, height);
			FruitPosition = { (std::rand() % (xFields - 1)) * (float)fieldSize, (std::rand() % (yFields - 1)) * (float)fieldSize };


			sgl::Renderer2D::BeginScene(0.0f, 0.0f, window.GetWidth(), window.GetHeight());
			/* Draw Background */
			for (int y = 0; y < yFields; y++)
			{
				for (int x = 0; x < xFields; x++)
				{
					sgl::Vec4f color = { x / (float) xFields, 0.4f, y / (float) yFields, bgOpacity };
					sgl::Renderer2D::DrawQuad({ x * fieldSize + (fieldSize / 2.f), y * fieldSize + (fieldSize / 2.f) }, { fieldSize - 0.1f * fieldSize, fieldSize - 0.1f * fieldSize }, color);
				}
			}
			sgl::Renderer2D::EndScene();
		}
		else if (GameState == Playing)
		{
			showSettings = false;
			while (clock.Restart().asMilliseconds<float>() < 100);

			/* Keyboard Input */
			if (sgl::Input::IsKeyPressed(sgl::Key::W))
				direction = dir::w;
			if (sgl::Input::IsKeyPressed(sgl::Key::A))
				direction = dir::a;
			if (sgl::Input::IsKeyPressed(sgl::Key::S))
				direction = dir::s;
			if (sgl::Input::IsKeyPressed(sgl::Key::D))
				direction = dir::d;

			/* Setting the Tail */
			for (int i = SnakePositions.size() - 1; i > 0; i--)
				SnakePositions[i] = SnakePositions[i - 1];

			/* Move Snake */
			if (direction == dir::w)
				SnakePositions[0].y += fieldSize;
			if (direction == dir::a)
				SnakePositions[0].x -= fieldSize;
			if (direction == dir::s)
				SnakePositions[0].y -= fieldSize;
			if (direction == dir::d)
				SnakePositions[0].x += fieldSize;

			// Collision with Fruit
			if (SnakePositions[0].x == FruitPosition.x && SnakePositions[0].y == FruitPosition.y)
			{
				FruitPosition = { (std::rand() % (xFields - 1)) * (float)fieldSize, (std::rand() % (yFields - 1)) * (float)fieldSize };
				SnakePositions.push_back({ -100.0f, -100.0f });
				score++;
			}
			// Collision with border
			if (SnakePositions[0].x < 0) SnakePositions[0].x = (xFields - 1) * fieldSize;
			if (SnakePositions[0].y < 0) SnakePositions[0].y = (yFields - 1) * fieldSize;
			if (SnakePositions[0].x >= xFields * fieldSize) SnakePositions[0].x = 0;
			if (SnakePositions[0].y >= yFields * fieldSize) SnakePositions[0].y = 0;
			// Collision with itself
			for (std::size_t i = 1; i < SnakePositions.size(); i++)
				if (SnakePositions[0].x == SnakePositions[i].x && SnakePositions[0].y == SnakePositions[i].y)
					GameState = Dead;

			sgl::Renderer::Clear(GL_COLOR_BUFFER_BIT);
			sgl::Renderer::BeginScene(window);     

			/* Render Score */
			std::string scoreDisp = std::string("Score: ") + std::to_string(score);
			ImGui::GetForegroundDrawList()->AddText(font, 48.0f, ImGui::GetWindowPos(), 0xffffffff, scoreDisp.c_str());

			/* Draw Field */
			for (float y = 0; y < yFields; y++)
			{
				for (float x = 0; x < xFields; x++)
				{
					sgl::Vec4f color = { x / (float)xFields, 0.4f, y / (float)yFields, bgOpacity };
					sgl::Renderer::DrawQuad({ x * fieldSize + (fieldSize/2), y * fieldSize + (fieldSize/2) }, { (float)fieldSize, (float)fieldSize }, FrameTex, color);
				}
			}
			/* Draw Snake */
			for (int i = 0; i < SnakePositions.size(); i++)
			{
				if (i == 0)
					sgl::Renderer::DrawQuad({ SnakePositions[i].x + (float)(fieldSize / 2.f), SnakePositions[i].y + (float)(fieldSize / 2.f) }, { (float)fieldSize, (float)fieldSize }, FrameTex, { startColor.r, startColor.g, startColor.b, startColor.a });
				else {
					glm::vec4 c = glm::lerp(startColor, endColor, (float) i / SnakePositions.size());
					sgl::Renderer::DrawQuad({ SnakePositions[i].x + (float)(fieldSize / 2.f), SnakePositions[i].y + (float)(fieldSize / 2.f) }, { (float)fieldSize, (float)fieldSize }, FrameTex, { c.r, c.g, c.b, c.a });
				}
			}
			/* Draw Fruit */
			sgl::Renderer::DrawQuad({ FruitPosition.x + (fieldSize / 2), FruitPosition.y + (fieldSize / 2) }, { (float)fieldSize, (float)fieldSize }, FrameTex);
			sgl::Renderer::EndScene();
		}
		else if (GameState == Dead)
		{
			if (score >= highscore)
				highscore = score;
			score = 0;
			GameState = MainMenu;
			SnakePositions.clear();
			for (std::size_t i = 0; i < 5; i++)
				SnakePositions.push_back({ -100.0f, -100.0f });
		}
		else if (GameState == Close)
		{
			window.Close();
		}

		sgl::ImGuiRender();
	}

	return EXIT_SUCCESS;
}
