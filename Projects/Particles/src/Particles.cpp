#include "Particles.h"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/compatibility.hpp>

Particles::Particles(uint32_t maxParticles)
{
	m_Particles.resize(maxParticles);
}

void Particles::Emit(const EmissionSettings &settings)
{
	unsigned int emitted = 0;
	for (auto &particle : m_Particles)
	{
		if (emitted > settings.emmissionCount)
			break;
		if (particle.active)
			continue;

		// Create new Particle
		particle.active = true;
		particle.lifetime = sgl::Random::Float(0.9f, 1.1f) * settings.lifetime;
		particle.rotation = sgl::Random::Float(0, 360);
		particle.remainingLife = particle.lifetime;
		particle.pos = settings.emitter;
		particle.size = settings.size;
		particle.speed = { sgl::Random::Float(-1.0f, 1.0f) * settings.speed, sgl::Random::Float(-1.0f, 1.0f) * settings.speed };
		particle.startColor = settings.startColor;
		particle.endColor = settings.endColor;
		emitted++;
	}
}

void Particles::OnUpdate(sgl::Time dt)
{
	float time = dt.asSeconds<float>();

	for (auto &particle : m_Particles)
	{
		if (!particle.active)
			continue;
		if (particle.remainingLife <= 0.0f)
			particle.active = false;

		particle.remainingLife -= time;
		particle.pos += particle.speed;
	}
}

void Particles::OnRender()
{
	for (auto &particle : m_Particles)
	{
		if (!particle.active)
			continue;
		glm::vec4 color = glm::lerp(particle.endColor, particle.startColor, particle.remainingLife / particle.lifetime);
		sgl::Renderer2D::DrawRotatedQuad({ particle.pos.x, particle.pos.y, 0.0f }, { particle.size.x, particle.size.y }, { color.r, color.g, color.b, particle.remainingLife / particle.lifetime }, particle.rotation);
	}
}

void Particles::Clear()
{
	for (auto &particle : m_Particles)
		particle.active = false;
}
