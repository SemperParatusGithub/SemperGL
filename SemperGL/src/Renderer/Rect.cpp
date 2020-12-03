#include "Rect.h"

namespace SemperGL
{



	Rect::Rect(const Vec2f &position, const Vec2f &size, const Vec4f &color)
	{
		m_Position = position;
		m_Size = size;
		m_Color = color;
	}

	void Rect::SetColor(const Vec4f &color)
	{
		m_Color = color;
	}

	void Rect::SetTexture(const Texture &texture)
	{
		m_Texture = &texture;
	}

	Vec4f Rect::GetColor() const
	{
		return m_Color;
	}

	const Texture &Rect::GetTexture() const
	{
		return *m_Texture;
	}

	void Rect::SetPosition(const Vec2f &position)
	{
		m_Position = position;
	}

	void Rect::SetSize(const Vec2f &size)
	{
		m_Size = size;
	}

	Vec2f Rect::GetPosition() const
	{
		return m_Position;
	}

	Vec2f Rect::GetSize() const
	{
		return m_Size;
	}

	void Rect::Move(const Vec2f &offset)
	{
		m_Position.x += offset.x;
		m_Position.y += offset.y;
	}

	void Rect::Scale(const Vec2f scale)
	{
		m_Size.x *= scale.x;
		m_Size.y *= scale.y;
	}

	void Rect::Rotate(float rotation)
	{
		m_Rotation += rotation;
	}

	void Rect::SetRotation(float rotation)
	{
		m_Rotation = rotation;
	}

	float Rect::GetRotation() const
	{
		return m_Rotation;
	}

}