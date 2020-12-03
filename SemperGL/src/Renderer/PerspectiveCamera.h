#pragma once

#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <unordered_map>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "Events/Event.h"

namespace SemperGL
{

	class PerspectiveCamera
	{
	public:
		PerspectiveCamera(const glm::vec3 &cameraPosition, float mouseSensitivity);

		void OnEvent(Event &e);
		glm::mat4 GetProjViewMatrix(int width, int height) const;

		inline void SetOrientation(float yaw, float pitch) { m_Yaw = yaw; m_Pitch = pitch; RecalculateCameraVectors(); }
		inline float GetYaw() const { return m_Yaw; }
		inline float GetPitch() const { return m_Pitch; }

		void SetPosition(const glm::vec3 &position) { m_CameraPosition = position; }
		inline glm::vec3 GetPosition() const { return m_CameraPosition; }
		void Move(const glm::vec3 &offset);

	private:
		void RecalculateCameraVectors();

	private:
		glm::vec3 m_CameraPosition;
		glm::vec3 m_Front, m_Up, m_Right;
		glm::vec2 lastMousePos;

		float m_Yaw, m_Pitch;

		float m_MouseSensitivity;
	};

}

#endif

/*
	if (sgl::Input::IsKeyPressed(sgl::Key::W))
		camera.Move({ 0.1f, 0.0f, 0.0f });
	if (sgl::Input::IsKeyPressed(sgl::Key::S))
		camera.Move({ -0.1f, 0.0f, 0.0f });

	if (sgl::Input::IsKeyPressed(sgl::Key::A))
		camera.Move({ 0.0f, 0.0f, -0.1f });
	if (sgl::Input::IsKeyPressed(sgl::Key::D))
		camera.Move({ 0.0f, 0.0f, 0.1f });

	if (sgl::Input::IsKeyPressed(sgl::Key::Space))
		camera.Move({ 0.0f, 0.1f, 0.0f });
	if (sgl::Input::IsKeyPressed(sgl::Key::LeftShift))
		camera.Move({ 0.0f, -0.1f, 0.0f });
*/