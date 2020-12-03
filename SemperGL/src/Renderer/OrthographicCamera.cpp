#include "OrthographicCamera.h"

namespace SemperGL
{

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
	{
		m_Position = { 0.0f, 0.0f, 0.0f };
		m_Zoom = 1.0f;
		m_ProjMatrix = glm::ortho(left, right, bottom, top, 0.0f, 100.0f);
		m_ViewMatrix = glm::mat4(1);
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjMatrix = glm::ortho(left, right, bottom, top, 0.0f, 100.0f);
	}

	void OrthographicCamera::SetPosition(Vec2f position)
	{
		m_Position = { position.x, position.y, 0.0f };
	}

	Vec3f OrthographicCamera::GetPosition() const
	{
		return { m_Position.x, m_Position.y, m_Position.z };
	}

	void OrthographicCamera::Move(Vec2f offset)
	{
		m_Position.x += offset.x;
		m_Position.y += offset.y;
		m_ViewMatrix = glm::translate(glm::mat4(1), m_Position);
		m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	void OrthographicCamera::Zoom(float zoom)
	{
		m_Zoom *= zoom;
		m_Position.z = zoom;
		m_ViewMatrix = glm::translate(glm::mat4(1), m_Position);
		//m_ViewMatrix = glm::inverse(m_ViewMatrix);
	}

	glm::mat4 OrthographicCamera::GetProjViewMatrix() const
	{
		return m_ProjMatrix * m_ViewMatrix;
	}

}