#include <SemperGL/SemperGL.h>


int main()
{
	SemperGL::Core::Init();
	SemperGL::Window window("Snake", 1280, 720);

	sgl::Texture texture("testTexture.png");

	float texturedQuadPosition[2] = { 200.0f, 200.0f };
	float texturedQuadSize[2] = { 200.0f, 200.0f };

	float coloredQuadPosition[2] = { 400.0f, 200.0f };
	float coloredQuadSize[2] = { 200.0f, 200.0f };

	while (window.IsOpen())
	{
		sgl::ImGuiUtil::BeginFrame();
		window.OnUpdate();
		window.Clear();

		ImGui::Begin("Settings");
		ImGui::Text("Colored Quad");
		ImGui::DragFloat2("##cQuadPos", coloredQuadPosition, 1.0f, 0.0f, 1280.0f);
		ImGui::DragFloat2("##cQuadSize", coloredQuadSize, 1.0f, 0.0f, 500.0f);
		ImGui::Text("Textured Quad");
		ImGui::DragFloat2("##tQuadPos", texturedQuadPosition, 1.0f, 0.0f, 1280.0f);
		ImGui::DragFloat2("##tQuadSize", texturedQuadSize, 1.0f, 0.0f, 500.0f);
		ImGui::End();

		sgl::Renderer2D::BeginScene(0, 0, 1280, 720);
		sgl::Renderer2D::DrawRotatedQuad({ coloredQuadPosition[0], coloredQuadPosition[1], 0.0f }, { coloredQuadSize[0], coloredQuadSize[1] }, { 1.0f, 0.0f, 0.0f, 1.0f }, 0.0f);
		sgl::Renderer2D::DrawQuad({ texturedQuadPosition[0], texturedQuadPosition[1], 0.0f }, { texturedQuadSize[0], texturedQuadSize[1] }, texture);
		sgl::Renderer2D::EndScene();

		sgl::ImGuiUtil::EndFrame();
	}
}