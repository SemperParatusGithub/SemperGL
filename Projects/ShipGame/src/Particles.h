#pragma once
#include <SemperGL/SemperGL.h>


struct EmissionSettings
{
	uint32_t emmissionCount = 1;
	float lifetime = 1;		// seconds
	float speed = 2.5f;
	glm::vec2 emitter = { 500.0f, 500.0f };
	glm::vec2 size = { 50.0f, 50.0f };
	glm::vec4 startColor;
	glm::vec4 endColor;
};

class ParticleSystem
{
public:
	ParticleSystem(uint32_t maxParticles);

	void Emit(const EmissionSettings &settings);
	void OnUpdate(sgl::Time dt);
	void OnRender();
	void Clear();

private:
	struct Particle
	{
		bool active;
		float lifetime;
		float remainingLife;
		float rotation;
		glm::vec2 pos, size;
		glm::vec2 speed;
		glm::vec4 startColor;
		glm::vec4 endColor;
	};
	std::vector<Particle> m_Particles;
};
