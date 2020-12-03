#include "Triangle.h"

namespace SemperGL
{


	Triangle::Triangle(const Vec2f &position, const Vec2f &size)
	{
		m_Position = position;
		m_Size = size;
	}

	void Triangle::SetColor(const Vec4f &color)
	{
		m_Color = color;
	}

	void Triangle::SetTexture(const Texture &texture)
	{
		m_Texture = &texture;
	}

	Vec4f Triangle::GetColor() const
	{
		return m_Color;
	}

	const Texture &Triangle::GetTexture() const
	{
		return *m_Texture;
	}

	void Triangle::SetPosition(const Vec2f &position)
	{
		m_Position = position;
	}

	void Triangle::SetSize(const Vec2f &size)
	{
		m_Size = size;
	}

	Vec2f Triangle::GetPosition() const
	{
		return m_Position;
	}

	Vec2f Triangle::GetSize() const
	{
		return m_Size;
	}

	void Triangle::Move(const Vec2f &offset)
	{
		m_Position.x += offset.x;
		m_Position.y += offset.y;
	}

	void Triangle::Scale(const Vec2f scale)
	{
		m_Size.x *= scale.x;
		m_Size.y *= scale.y;
	}

}