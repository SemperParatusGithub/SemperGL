#pragma once

#include "Util/Vectors.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace SemperGL
{

	class OrthographicCamera
	{
	public:
		OrthographicCamera(float left, float right, float bottom, float top);
		~OrthographicCamera() = default;

		void SetProjection(float left, float right, float bottom, float top);

		void SetPosition(Vec2f position);
		Vec3f GetPosition() const;

		void Move(Vec2f offset);
		void Zoom(float zoom);

		inline void SetZoom(float zoom)
		{ 
			m_Zoom = zoom;
			m_ViewMatrix = glm::translate(glm::mat4(1), m_Position);
			m_ViewMatrix = glm::inverse(m_ViewMatrix);
		}

		glm::mat4 GetProjViewMatrix() const;

	private:
		glm::vec3 m_Position;
		float m_Zoom;
		glm::mat4 m_ProjMatrix, m_ViewMatrix;
	};

}