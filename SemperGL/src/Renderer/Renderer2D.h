#pragma once
#include <array>

#include "Util/Shader.h"
#include "Texture.h"

#include "OrthographicCamera.h"
#include "PerspectiveCamera.h"

#include "Util/VertexArray.h"
#include "Util/VertexBuffer.h"
#include "Util/IndexBuffer.h"

#include "Triangle.h"
#include "Rect.h"

#include <glm/glm.hpp>

namespace SemperGL
{
	static const uint32_t MaxQuadCount = 100000;
	static const uint32_t MaxVertexCount = MaxQuadCount * 4;
	static const uint32_t MaxIndexCount = MaxQuadCount * 6;
	static const uint32_t MaxTextures = 16;

	struct RenderingStats
	{
		uint32_t quads = 0;
		uint32_t indices = 0;
		uint32_t vertices = 0;
		uint32_t triangles = 0;
		uint32_t drawCalls = 0;
	};
	struct QuadVertex
	{
		glm::vec4 position;
		glm::vec4 color;
		glm::vec2 texCoords;
		float texIndex;
	};
	struct TriangleVertex
	{
		glm::vec4 position;
		glm::vec4 color;
		glm::vec2 texCoords;
		float texIndex;
	};

	class Renderer2D
	{
	public:
		static void Init();
		static void Shutdown();

		static void BeginScene(float x, float y, float width, float height);
		static void EndScene();
		static void Flush();

		static void Draw(const Rect &rect);
		static void Draw(const Triangle &triangle);

		static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
		static void DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, const glm::vec4 &tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

		static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation);
		static void DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, float rotation, const glm::vec4 &tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

		static void DrawIndexed(const VertexArray &vertexArray, const Shader &shader, uint32_t count = 0);

		static void ResetStats();
		static RenderingStats GetStats();

	private:
		static Renderer2D *GetInstance();
		void BeginScene();

		void InitImpl();
		void ShutdownImpl();

		void BeginSceneImpl(float x, float y, float width, float height);
		void BeginSceneImpl();
		void EndSceneImpl();
		void FlushImpl();

		void DrawImpl(const Rect &rect);
		void DrawImpl(const Triangle &triangle);

		void DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color);
		void DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, const glm::vec4 &tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

		void DrawRotatedQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation);
		void DrawRotatedQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, float rotation, const glm::vec4 &tintColor = { 1.0f, 1.0f, 1.0f, 1.0f });

		void DrawIndexedImpl(const VertexArray &vertexArray, const Shader &shader, uint32_t count = 0);

		void ResetStatsImpl();
		RenderingStats GetStatsImpl();

	private:
		uint32_t QuadVAO = 0, QuadVBO = 0, QuadEBO = 0;
		uint32_t QuadIndexCount = 0;

		glm::vec4 QuadVertexPositions[4];
		glm::vec2 QuadTextureCoords[4];

		QuadVertex *QuadBuffer = nullptr;
		QuadVertex *QuadBufferPtr = nullptr;

		Shader *QuadShader = nullptr;

		Texture *whiteTex = nullptr;
		std::array<const Texture *, MaxTextures> textures;

		RenderingStats stats;
	};
}