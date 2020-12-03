#include "Level.h"


Level::Level() : 
	m_Pillars(6),
	m_PillarTex("res/textures/Pillar.jpg")
{
	// Setup Pillars
	for (auto &[bottom, top, passed] : m_Pillars)
	{
		bottom.SetTexture(m_PillarTex);
		bottom.SetSize({ 200.0f, 800.0f });

		top.SetTexture(m_PillarTex);
		top.SetSize({ 200.0f, 800.0f });
	}

	Reset();
}

void Level::Reset()
{
	// Reset the Pillars 
	float xPos = 2500.0;
	for (auto &[bottom, top, passed] : m_Pillars)
	{
		float gap = sgl::Random::Float(250.0f, 350.0f);
		float offset = sgl::Random::Float(-300.0f, -100.0f);
		bottom.SetPosition({ xPos, offset });
		top.SetPosition({ xPos, offset + bottom.GetSize().y / 2.0f + gap + top.GetSize().y / 2.0f });
		passed = false;
		xPos += 500.0;
	}
}

void Level::OnUpdate(sgl::Time deltaTime, float horizontalVelocity)
{
	for (auto &[bottom, top, passed] : m_Pillars)
	{
		sgl::Vec2f movement { -horizontalVelocity * deltaTime.asSeconds<float>(), 0.0f };
		bottom.Move(movement);
		top.Move(movement);

		// Move Pillar to the beginning (reuse)
		if (bottom.GetPosition().x <= -500.0f) 
		{
			float gap = sgl::Random::Float(250.0f, 350.0f);
			float offset = sgl::Random::Float(-300.0f, -100.0f);
			bottom.SetPosition({ 2500.0f, offset });
			top.SetPosition({ 2500.0f, offset + bottom.GetSize().y / 2.0f + gap + top.GetSize().y / 2.0f });
			passed = false;
		}
	}
}

void Level::OnRender()
{
	// Draw the Pillars
	for (const auto &[bottom, top, passed] : m_Pillars)
	{
		sgl::Renderer2D::Draw(bottom);
		sgl::Renderer2D::Draw(top);
	}
}

bool Level::CheckForCollision(Player &player)
{
	auto &p = player.GetPosition();
	auto &s = player.GetSize();

	for (auto &[bottom, top, passed] : m_Pillars)
	{
		// Check if player is in between two pillars
		if (bottom.GetPosition().x >= p.x - s.x / 2 - bottom.GetSize().x / 2 &&
			bottom.GetPosition().x <= p.x + s.x / 2 + bottom.GetSize().x / 2)
		{
			if (!passed) {
				passed = true;
				player.SetScore(player.GetScore() + 1);
				player.SetHorizontalVelocity(player.GetHorizontalVelocity() + 25.0f);
			}
			// Check if Player collides with the bottom pillar
			if (p.y - s.y / 2 <= bottom.GetPosition().y + bottom.GetSize().y / 2)
				return true;
			// Check if Player collides with the top pillar
			if (p.y + s.y / 2 >= top.GetPosition().y - top.GetSize().y / 2)
				return true;
		}
	}

	// Collision with bottom and top of the screen
	if (p.y >= 720.0f - s.y / 2 || p.y <= 0.0f + s.y / 2)
		return true;

	return false;
}
