#include "PerspectiveCamera.h"

#include "Events/KeyEvents.h"
#include "Events/MouseEvents.h"
#include "Events/WindowEvents.h"

#include "Input/Input.h"

namespace SemperGL
{

	glm::mat4 PerspectiveCamera::GetProjViewMatrix(int width, int height) const
	{
		glm::mat4 proj = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);
		glm::mat4 view = glm::lookAt(m_CameraPosition, m_CameraPosition + m_Front, m_Up);
		return { proj * view };
	}

	PerspectiveCamera::PerspectiveCamera(const glm::vec3 &cameraPosition, float mouseSensitivity) :
		m_CameraPosition(cameraPosition),
			m_MouseSensitivity(mouseSensitivity)
	{
		{
			m_Yaw = 90.0f;
			m_Pitch = 0.0f;

			lastMousePos = { Input::GetMouseX(), Input::GetMouseY() };

			RecalculateCameraVectors();
		}
	}

	void PerspectiveCamera::OnEvent(Event &e)
	{
		if (e.isType<MouseMovedEvent>())
		{
			float xOffset = e.GetMousePosition().x - lastMousePos.x;
			float yOffset = e.GetMousePosition().y - lastMousePos.y;

			xOffset *= m_MouseSensitivity;
			yOffset *= m_MouseSensitivity;

			m_Yaw += xOffset;
			m_Pitch -= yOffset;

			if (m_Pitch > 89.0f)
				m_Pitch = 89.0f;
			if (m_Pitch < -89.0f)
				m_Pitch = -89.0f;

			RecalculateCameraVectors();
			lastMousePos = { e.GetMousePosition().x, e.GetMousePosition().y };
		}
	}

	void PerspectiveCamera::Move(const glm::vec3 &offset)
	{
		glm::vec3 forward(cos(glm::radians(m_Yaw)), 0.0f, sin(glm::radians(m_Yaw)));

		if (offset.x != 0.0f)
			m_CameraPosition += forward * offset.x;
		if (offset.z != 0.0f)
			m_CameraPosition += m_Right * offset.z;
		if (offset.y != 0.0f)
			m_CameraPosition.y += m_Up.y * offset.y;
	}

	void PerspectiveCamera::RecalculateCameraVectors()
	{
		glm::vec3 frontNew;
		frontNew.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
		frontNew.y = sin(glm::radians(m_Pitch));
		frontNew.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

		m_Front = glm::normalize(frontNew);
		m_Right = glm::normalize(glm::cross(m_Front, glm::vec3(0.0f, 1.0f, 0.0f)));  // Normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
		m_Up = glm::vec3(0.0f, 1.0f, 0.0f);											 // glm::normalize(glm::cross(this->Right, this->Front));
	}

}