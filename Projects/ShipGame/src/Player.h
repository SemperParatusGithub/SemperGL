#pragma once

#include <SemperGL/SemperGL.h>
#include "Particles.h"

const float maxVelocity = 1000.0f;

class Player
{
public:
	Player();
	~Player() = default;

	void OnUpdate(sgl::Time deltaTime);
	void OnRender();

	sgl::Vec2f GetPosition() const;
	sgl::Vec2f GetSize() const;

	void SetScore(unsigned int score);
	unsigned int GetScore() const;

	void SetHighscore(unsigned int highscore);
	unsigned int GetHighscore() const;

	void SetHorizontalVelocity(float velocity);
	float GetHorizontalVelocity() const;

private:
	sgl::Rect m_Body;
	sgl::Texture m_Texture;
	unsigned int m_Score, m_Highscore;

	float m_EnginePower, m_Gravity;
	float m_VerticalVelocity;
	float m_HorizontalVelocity;

	ParticleSystem m_EngineParticles;
	EmissionSettings m_EngineSettings;
};
