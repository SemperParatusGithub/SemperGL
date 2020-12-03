#include <SemperGL/SemperGL.h>


void EventCallback(sgl::Event &e);

float color[3] = { 1.0f, 1.0f, 1.0f };
int maxIterations = 200;
double screenSize[2] = { 1280.0f, 720.0f };
double offset[2] = { 0.0f, 0.0f };
double zoom = 200.0f;
float ReIm[2] = { 0, 0 };

int main()
{
	sgl::Core::Init();

	sgl::Window window("Mandelbrot", 1280, 720);
	window.SetVsync(true);
	window.SetMinimumSize(1280, 720);
	window.SetEventCallback(EventCallback);

	sgl::Clock clock;

	ImFont *openSansRegular = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Regular.ttf", 32.0f);
	ImFont *openSansRegularBig = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Regular.ttf", 50.0f);
	ImFont *openSansBold = ImGui::GetIO().Fonts->AddFontFromFileTTF("res/fonts/OpenSans/OpenSans-Bold.ttf", 32.0f);
	ImGui::GetIO().FontDefault = openSansRegular;
	ImGui::GetStyle().WindowMinSize = ImVec2 { 500.0f, 450.0f };

	bool mandelbrot = true, juliaSet = false;

	float vertices[] = {
		-1.0f, -1.0f,
		 1.0f, -1.0f,
		 1.0f,  1.0f,
		-1.0f,  1.0f
	};
	uint32_t indices[] = {
		0, 1, 2, 2, 3, 0
	};
	
	sgl::Shader mandelbrotShader(sgl::Shader::LoadFromGLSLFiles("res/shaders/Mandelbrot.vert.glsl", "res/shaders/Mandelbrot.frag.glsl"));
	sgl::Shader juliaSetShader(sgl::Shader::LoadFromGLSLFiles("res/shaders/JuliaSet.vert.glsl", "res/shaders/JuliaSet.frag.glsl"));
	
	sgl::VertexArray va;
	va.Bind();
	sgl::IndexBuffer ib(6, indices);
	ib.Bind();
	sgl::VertexBuffer vb(sizeof(vertices), vertices);
	vb.Bind();
	
	va.AddVertexBuffer(vb);
	va.AddIndexBuffer(ib);
	va.AddAttribute(0, 2, GL_FLOAT, 2 * sizeof(float), (const void *) 0);

	while (window.IsOpen())
	{
		sgl::ImGuiUtil::BeginFrame();
		window.OnUpdate();

		auto dt = clock.Restart().asMilliseconds<double>();

		if (sgl::Input::IsKeyPressed(sgl::Key::W))
			offset[1] -= dt / zoom;
		if (sgl::Input::IsKeyPressed(sgl::Key::S))
			offset[1] += dt / zoom;
		if (sgl::Input::IsKeyPressed(sgl::Key::A))
			offset[0] += dt / zoom;
		if (sgl::Input::IsKeyPressed(sgl::Key::D))
			offset[0] -= dt / zoom;

		// ImGui
		{
			// FPS Counter
			char framerate[20];
			sprintf_s(framerate, 20, "FPS: %.2f", ImGui::GetIO().Framerate);
			ImVec2 pos = { ImGui::GetWindowPos().x * 0.9f, ImGui::GetWindowPos().y * 0.9f };
			ImGui::GetForegroundDrawList()->AddText(openSansRegular, 45.0f, pos, 0xffffffff, framerate);

			ImGui::PushFont(openSansBold);
			ImGui::Begin("Settings");

			ImGui::PushFont(openSansRegular);
			if (ImGui::Checkbox(" Mandelbrot Set", &mandelbrot))
				juliaSet = false;
			if (ImGui::Checkbox(" Julia Set", &juliaSet))
				mandelbrot = false;

			ImGui::SliderFloat3("Coloring", color, 0.0f, 1.0f);
			ImGui::SliderInt("Max Iterations", &maxIterations, 0, 1000);

			ImGui::Text("Position: %.2f, %.2f", offset[0], offset[1]);
			ImGui::Text("Zoom: %.2f", zoom);

			if (juliaSet)
			{
				ImGui::DragFloat("Realteil", &ReIm[0], 0.005f, -1.0f, 1.0f);
				ImGui::DragFloat("Imaginärteil", &ReIm[1], 0.005f, -1.0f, 1.0f);
			}
			if (ImGui::Button("Reset", ImVec2 { ImGui::GetWindowSize().x / 5.0f, 50.0f}))
			{
				mandelbrot = true, juliaSet = false;
				color[0] = 1.0f, color[1] = 1.0f, color[2] = 1.0f;
				screenSize[0] = window.GetWidth(), screenSize[1] = window.GetHeight();
				offset[0] = 0.0f, offset[1] = 0.0f;
				ReIm[0] = 0, ReIm[1] = 0;
				maxIterations = 200;
				zoom = 200.0f;
			}

			ImGui::PopFont();
			ImGui::PopFont();
			ImGui::End();
		}

		mandelbrotShader.Bind();
		mandelbrotShader.SetUniform3f("u_Color", color[0] * 10, color[1] * 10, color[2] * 10);
		mandelbrotShader.SetUniform1i("u_MaxIterations", maxIterations);
		mandelbrotShader.SetUniform2d("u_ScreenSize", screenSize[0], screenSize[1]);
		mandelbrotShader.SetUniform1d("u_Zoom", zoom);
		mandelbrotShader.SetUniform2d("u_Offset", offset[0], offset[1]);

		juliaSetShader.Bind();
		juliaSetShader.SetUniform3f("u_Color", color[0] * 10, color[1] * 10, color[2] * 10);
		juliaSetShader.SetUniform1i("u_MaxIterations", maxIterations);
		juliaSetShader.SetUniform2d("u_ScreenSize", screenSize[0], screenSize[1]);
		juliaSetShader.SetUniform1d("u_Zoom", zoom);
		juliaSetShader.SetUniform2d("u_Offset", offset[0], offset[1]);
		juliaSetShader.SetUniform1f("u_Re", ReIm[0]);
		juliaSetShader.SetUniform1f("u_Im", ReIm[1]);

		window.Clear();
		if(mandelbrot)
			sgl::Renderer2D::DrawIndexed(va, mandelbrotShader);
		else if(juliaSet)
			sgl::Renderer2D::DrawIndexed(va, juliaSetShader);

		sgl::ImGuiUtil::EndFrame();
	}
}

void EventCallback(sgl::Event &e)
{
	if (e.isType<sgl::WindowResizeEvent>())
	{
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		screenSize[0] = e.GetWidth();
		screenSize[1] = e.GetHeight();
	}

	if (e.isType<sgl::MouseScrolledEvent>())
		if(zoom >= 50.0f || e.GetOffset().y > 0)
			zoom += e.GetOffset().y * zoom / 5;
}