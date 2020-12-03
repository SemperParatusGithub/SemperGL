#pragma once

#include <SemperGL/SemperGL.h>
#include <tuple>
#include "Player.h"

using Pillar = std::tuple<sgl::Rect, sgl::Rect, bool>;
// bool...true if the player has past the pillar

class Level
{
public:
	Level();
	~Level() = default;

	void Reset();
	void OnUpdate(sgl::Time deltaTime, float horizontalVelocity);
	void OnRender();

	bool CheckForCollision(Player &player);

private:
	std::vector<Pillar> m_Pillars;
	sgl::Texture m_PillarTex;
};
