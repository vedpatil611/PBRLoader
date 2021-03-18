#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>

Camera::Camera(glm::vec3 pos, glm::vec3 up, float yaw, float pitch, float movementSpeed, float turnSpeed)
	:m_Pos(pos), m_Up(up), m_Yaw(yaw), m_Pitch(pitch), m_MovementSpeed(movementSpeed), m_TurnSpeed(turnSpeed), m_Front(0.0f, 0.0f, -1.0f)
{
	update();
}

Camera::~Camera()
{
}

glm::mat4 Camera::getViewMatrix() const
{
	return glm::lookAt(m_Pos, m_Pos + m_Front, m_Up);
}

void Camera::handleInputs(bool* keys, float xChange, float yChange, float delta)
{
	if (keys[GLFW_MOUSE_BUTTON_1])
	{
		xChange *= m_TurnSpeed * delta;
		yChange *= m_TurnSpeed * delta;

		m_Yaw += xChange;
		m_Pitch += yChange;

		if (m_Pitch >  89) m_Pitch =  89;
		if (m_Pitch < -89) m_Pitch = -89;

		float velocity = m_MovementSpeed * delta;
		if (keys[GLFW_KEY_W])
		{
			m_Pos += m_Front * velocity;
		}
		if (keys[GLFW_KEY_S])
		{
			m_Pos -= m_Front * velocity;
		}
		if (keys[GLFW_KEY_D])
		{
			m_Pos += m_Right * velocity;
		}
		if (keys[GLFW_KEY_A])
		{
			m_Pos -= m_Right * velocity;
		}
		if (keys[GLFW_KEY_E])
		{
			m_Pos += m_WorldUp * velocity;
		}
		if (keys[GLFW_KEY_Q])
		{
			m_Pos -= m_WorldUp * velocity;
		}

		update();
	}
}

void Camera::update()
{
	m_Front.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
	m_Front.y = sin(glm::radians(m_Pitch));
	m_Front.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));

	m_Right = glm::normalize(glm::cross(m_Front, m_WorldUp));
	m_Up = glm::normalize(glm::cross(m_Right, m_Front));
}
