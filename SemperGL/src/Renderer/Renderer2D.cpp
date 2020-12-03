#include "Renderer2D.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


namespace SemperGL
{
	void Renderer2D::InitImpl()
	{
		// Init Quad Data
		QuadBuffer = new QuadVertex[MaxVertexCount];

		glCreateVertexArrays(1, &QuadVAO);
		glBindVertexArray(QuadVAO);

		glCreateBuffers(1, &QuadVBO);
		glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
		glBufferData(GL_ARRAY_BUFFER, MaxVertexCount * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, position));

		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, texCoords));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (const GLvoid *) offsetof(QuadVertex, texIndex));

		uint32_t *indices = new uint32_t[MaxIndexCount];
		uint32_t offset = 0;
		for (int i = 0; i < MaxIndexCount; i += 6)
		{
			indices[i + 0] = 0 + offset;
			indices[i + 1] = 1 + offset;
			indices[i + 2] = 2 + offset;

			indices[i + 3] = 2 + offset;
			indices[i + 4] = 3 + offset;
			indices[i + 5] = 0 + offset;

			offset += 4;
		}
		glCreateBuffers(1, &QuadEBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadEBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, MaxIndexCount * sizeof(uint32_t), indices, GL_STATIC_DRAW);


		QuadShader = new Shader(Shader::LoadFromGLSLFile("res/shaders/Basic.shader"));
		QuadShader->Bind();

		QuadVertexPositions[0] = { -0.5f, -0.5f, 0.0f, 1.0f };
		QuadVertexPositions[1] = { 0.5f, -0.5f, 0.0f, 1.0f };
		QuadVertexPositions[2] = { 0.5f, 0.5f, 0.0f, 1.0f };
		QuadVertexPositions[3] = { -0.5f, 0.5f, 0.0f, 1.0f };

		QuadTextureCoords[0] = { 0.0f, 0.0f };
		QuadTextureCoords[1] = { 1.0f, 0.0f };
		QuadTextureCoords[2] = { 1.0f, 1.0f };
		QuadTextureCoords[3] = { 0.0f, 1.0f };

		// Create White Texture
		whiteTex = new Texture("res/textures/WhiteTex.png");

		for (auto &tex : textures)
			tex = whiteTex;

		int samplers[MaxTextures];
		for (int i = 0; i < MaxTextures; i++)
			samplers[i] = i;
		auto loc = glGetUniformLocation(QuadShader->GetID(), "u_Textures");
		glUniform1iv(loc, MaxTextures, samplers);
	}

	void Renderer2D::ShutdownImpl()
	{
		delete[] QuadBuffer;
		glDeleteVertexArrays(1, &QuadVAO);
		glDeleteBuffers(1, &QuadVBO);
		glDeleteBuffers(1, &QuadEBO);
	}

	void Renderer2D::BeginSceneImpl(float x, float y, float width, float height)
	{
		QuadBufferPtr = QuadBuffer;
		glm::mat4 projView = glm::ortho(x, width, y, height);
		QuadShader->SetUniformMat4f("u_ProjView", projView);
	}

	void Renderer2D::BeginSceneImpl()
	{
		QuadBufferPtr = QuadBuffer;
	}

	void Renderer2D::EndSceneImpl()
	{
		GLsizeiptr size = (uint8_t *) QuadBufferPtr - (uint8_t *) QuadBuffer;
		glBindBuffer(GL_ARRAY_BUFFER, QuadVBO);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, QuadBuffer);

		Flush();
	}

	void Renderer2D::FlushImpl()
	{
		for (std::size_t i = 0; i < textures.size(); i++)
			textures[i]->Bind(i);

		for (std::size_t i = 0; i < textures.size(); i++)
			textures[i] = whiteTex;

		glBindVertexArray(QuadVAO);
		glDrawElements(GL_TRIANGLES, QuadIndexCount, GL_UNSIGNED_INT, nullptr);

		QuadIndexCount = 0;
		stats.drawCalls += 1;
	}

	void Renderer2D::DrawImpl(const Rect &rect)
	{
		glm::vec3 position = { rect.GetPosition().x, rect.GetPosition().y, 0.0f };
		glm::vec2 size = { rect.GetSize().x, rect.GetSize().y };
		glm::vec4 color { rect.GetColor().x, rect.GetColor().y, rect.GetColor().z, rect.GetColor().w };
		
		if (rect.hasTexture())
			GetInstance()->DrawRotatedQuadImpl(position, size, rect.GetTexture(), rect.GetRotation());
		else
			GetInstance()->DrawRotatedQuadImpl(position, size, color, rect.GetRotation());
	}

	void Renderer2D::DrawImpl(const Triangle &triangle)
	{
	}

	void Renderer2D::DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
	{
		if (QuadIndexCount >= MaxIndexCount)
		{
			EndScene();
			Flush();
			BeginScene();
		}

		GLfloat textureIndex = 0.0f;

		QuadBufferPtr->position = { position.x - size.x / 2, position.y - size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = color;
		QuadBufferPtr->texCoords = { 0.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = { position.x + size.x / 2, position.y - size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = color;
		QuadBufferPtr->texCoords = { 1.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = { position.x + size.x / 2, position.y + size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = color;
		QuadBufferPtr->texCoords = { 1.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = { position.x - size.x / 2, position.y + size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = color;
		QuadBufferPtr->texCoords = { 0.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadIndexCount += 6;

		stats.triangles += 2;
		stats.vertices += 4;
		stats.indices += 6;
		stats.quads += 1;
	}

	void Renderer2D::DrawQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, const glm::vec4 &tintColor)
	{
		if (QuadIndexCount >= MaxIndexCount)
		{
			EndScene();
			Flush();
			BeginScene();
		}

		GLfloat textureIndex = 0.0f;

		for (std::size_t i = 1; i < textures.size(); i++)
		{
			if (textures[i]->GetID() == texture.GetID()) {
				textureIndex = static_cast<GLfloat>(i);
				break;
			}
			else if (textures[i]->GetID() == whiteTex->GetID()) {
				textureIndex = static_cast<GLfloat>(i);
				textures[i] = &texture;
				break;
			}
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		QuadBufferPtr->position = { position.x - size.x / 2, position.y - size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 0.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = { position.x + size.x / 2, position.y - size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 1.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = { position.x + size.x / 2, position.y + size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 1.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = { position.x - size.x / 2, position.y + size.y / 2, position.z, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 0.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadIndexCount += 6;

		stats.triangles += 2;
		stats.vertices += 4;
		stats.indices += 6;
		stats.quads += 1;
	}

	void Renderer2D::DrawRotatedQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &tintColor, float rotation)
	{
		if (QuadIndexCount >= MaxIndexCount)
		{
			EndScene();
			Flush();
			BeginScene();
		}
		GLfloat textureIndex = 0.0f;
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		QuadBufferPtr->position = transform * glm::vec4 { 0.0f, 0.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 0.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = transform * glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 1.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = transform * glm::vec4 { 1.0f, 1.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 1.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = transform * glm::vec4 { 0.0f, 1.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 0.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadIndexCount += 6;

		stats.triangles += 2;
		stats.vertices += 4;
		stats.indices += 6;
		stats.quads += 1;
	}

	void Renderer2D::DrawRotatedQuadImpl(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, float rotation, const glm::vec4 &tintColor)
	{
		if (QuadIndexCount >= MaxIndexCount)
		{
			EndScene();
			Flush();
			BeginScene();
		}
		GLfloat textureIndex = 0.0f;

		for (std::size_t i = 1; i < textures.size(); i++)
		{
			if (textures[i]->GetID() == texture.GetID()) {
				textureIndex = static_cast<GLfloat>(i);
				break;
			}
			else if (textures[i]->GetID() == whiteTex->GetID()) {
				textureIndex = static_cast<GLfloat>(i);
				textures[i] = &texture;
				break;
			}
		}
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f }) * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

		QuadBufferPtr->position = transform * glm::vec4 { 0.0f, 0.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 0.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = transform * glm::vec4 { 1.0f, 0.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 1.0f, 0.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = transform * glm::vec4 { 1.0f, 1.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 1.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadBufferPtr->position = transform * glm::vec4 { 0.0f, 1.0f, 0.0f, 1.0f };
		QuadBufferPtr->color = tintColor;
		QuadBufferPtr->texCoords = { 0.0f, 1.0f };
		QuadBufferPtr->texIndex = textureIndex;
		QuadBufferPtr++;

		QuadIndexCount += 6;

		stats.triangles += 2;
		stats.vertices += 4;
		stats.indices += 6;
		stats.quads += 1;
	}

	void Renderer2D::DrawIndexedImpl(const VertexArray &vertexArray, const Shader &shader, uint32_t count)
	{
		int c = 0;
		count == 0 ? c = vertexArray.GetIndexBuffer()->GetCount() : c = count;

		vertexArray.Bind();
		shader.Bind();

		glDrawElements(GL_TRIANGLES, c, GL_UNSIGNED_INT, nullptr);
	}

	void Renderer2D::ResetStatsImpl()
	{
		stats.quads = 0;
		stats.indices = 0;
		stats.vertices = 0;
		stats.triangles = 0;
		stats.drawCalls = 0;
	}

	RenderingStats Renderer2D::GetStatsImpl()
	{
		return stats;
	}

	Renderer2D *Renderer2D::GetInstance()
	{
		static Renderer2D *Instance = new Renderer2D();
		return Instance;
	}

	void Renderer2D::BeginScene()
	{
		GetInstance()->BeginSceneImpl();
	}

	void Renderer2D::Init()
	{
		GetInstance()->InitImpl();
	}
	void Renderer2D::Shutdown()
	{
		GetInstance()->ShutdownImpl();
	}

	void Renderer2D::BeginScene(float x, float y, float width, float height)
	{
		GetInstance()->BeginSceneImpl(x, y, width, height);
	}
	void Renderer2D::EndScene()
	{
		GetInstance()->EndSceneImpl();
	}
	void Renderer2D::Flush()
	{
		GetInstance()->FlushImpl();
	}

	void Renderer2D::Draw(const Rect &rect)
	{
		GetInstance()->DrawImpl(rect);
	}
	void Renderer2D::Draw(const Triangle &triangle)
	{
		GetInstance()->DrawImpl(triangle);
	}

	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color)
	{
		GetInstance()->DrawQuadImpl(position, size, color);
	}
	void Renderer2D::DrawQuad(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, const glm::vec4 &tintColor)
	{
		GetInstance()->DrawQuadImpl(position, size, texture, tintColor);
	}

	void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const glm::vec4 &color, float rotation)
	{
		GetInstance()->DrawRotatedQuadImpl(position, size, color, rotation);
	}
	void Renderer2D::DrawRotatedQuad(const glm::vec3 &position, const glm::vec2 &size, const Texture &texture, float rotation, const glm::vec4 &tintColor)
	{
		GetInstance()->DrawRotatedQuadImpl(position, size, texture, rotation, tintColor);
	}

	void Renderer2D::DrawIndexed(const VertexArray &vertexArray, const Shader &shader, uint32_t count)
	{
		GetInstance()->DrawIndexedImpl(vertexArray, shader, count);
	}

	void Renderer2D::ResetStats()
	{
		GetInstance()->ResetStatsImpl();
	}
	RenderingStats Renderer2D::GetStats()
	{
		return GetInstance()->GetStatsImpl();
	}
}