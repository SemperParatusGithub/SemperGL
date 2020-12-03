#pragma once

#include "Util/Vectors.h"
#include "Texture.h"

namespace SemperGL
{
	class Renderer2D;

	class Triangle
	{
	public:
		Triangle() = default;
		Triangle(const Vec2f &position, const Vec2f &size);

		void SetColor(const Vec4f &color);
		void SetTexture(const Texture &texture);

		Vec4f GetColor() const;
		const Texture &GetTexture() const;

		void SetPosition(const Vec2f &position);
		void SetSize(const Vec2f &size);

		Vec2f GetPosition() const;
		Vec2f GetSize() const;

		void Move(const Vec2f &offset);
		void Scale(const Vec2f scale);

	private:
		friend class Renderer2D;
		bool hasTexture() const { return { m_Texture != nullptr }; }

	private:
		Vec2f m_Position { 0.0f, 0.0f };
		Vec2f m_Size { 200.0f, 200.0f };
		const Texture *m_Texture;
		Vec4f m_Color = { 0 };
	};

}