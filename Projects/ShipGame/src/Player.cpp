#include "Player.h"

Player::Player() :
	m_Body({ 600.0f, 400.0f }, { 16.0f * 5.0f, 9.0f * 5.0f }), // *7.0f
	m_Texture("res/textures/Roccat.png"),
	m_Score(0), m_Highscore(0),
	m_EnginePower(2.0f), m_Gravity(1.6f),
	m_VerticalVelocity(0.0f),
	m_HorizontalVelocity(500.0f),
	m_EngineParticles(1000)
{
	// Set Texture
	m_Body.SetTexture(m_Texture);

	// Setup Particles
	m_EngineSettings.size = { 15.0f, 15.0f };
	m_EngineSettings.startColor = { 1.0f, 0.0f, 0.0f, 1.0f };
	m_EngineSettings.endColor = { 0.9f, 0.4f, 0.0f, 1.0f };
}

void Player::OnUpdate(sgl::Time deltaTime)
{
	// Update Particles
	m_EngineParticles.OnUpdate(deltaTime);
	m_EngineSettings.emitter = { GetPosition().x, GetPosition().y };
	m_EngineSettings.speed = m_HorizontalVelocity / 200.0f;

	if (sgl::Input::IsKeyPressed(sgl::Key::Space) || sgl::Input::IsMouseButtonPressed(sgl::Mouse::Button0))
	{
		m_VerticalVelocity += m_EnginePower * deltaTime.asSeconds<float>();
		if (m_VerticalVelocity < 0.0f)
			m_VerticalVelocity += m_EnginePower * 2.0f * deltaTime.asSeconds<float>();

		// Emit particles
		m_EngineParticles.Emit(m_EngineSettings);
	}
	else {
		m_VerticalVelocity -= m_Gravity * deltaTime.asSeconds<float>();
	}
	// Move and rotate player
	m_Body.Move({ 0.0f, m_VerticalVelocity * (float)deltaTime.asMilliseconds<float>() });
	m_Body.SetRotation(m_VerticalVelocity * 75);
}

void Player::OnRender()
{
	m_EngineParticles.OnRender();
	sgl::Renderer2D::Draw(m_Body);
}

sgl::Vec2f Player::GetPosition() const
{
	return m_Body.GetPosition();
}

sgl::Vec2f Player::GetSize() const
{
	return m_Body.GetSize();
}

void Player::SetScore(unsigned int score)
{
	m_Score = score;
}

unsigned int Player::GetScore() const
{
	return m_Score;
}

void Player::SetHighscore(unsigned int highscore)
{
	m_Highscore = highscore;
}

unsigned int Player::GetHighscore() const
{
	return m_Highscore;
}

void Player::SetHorizontalVelocity(float velocity)
{
	if (velocity <= maxVelocity)
		m_HorizontalVelocity = velocity;
}

float Player::GetHorizontalVelocity() const
{
	return m_HorizontalVelocity;
}