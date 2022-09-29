#include "camera.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.h"
#include <iostream>

Camera::Camera(glm::vec3 position, glm::vec3 target, glm::vec3 worldup)
{
	Position = position;
	Worldup = worldup;
	Forward = glm::normalize(position-target);
	Right = glm::normalize(glm::cross(Worldup,Forward));
	Up = glm::normalize(glm::cross(Forward,Right));
}
Camera::Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup)
{
	Position = position;
	Worldup = worldup;
	Forward.x = cos(glm::radians(pitch)) * sin(glm::radians(yaw));
	Forward.y = sin(glm::radians(pitch));
	Forward.z= cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	/*Forward.x = 0;
	Forward.y = 0;
	Forward.z = 3.0f;
	std::cout << "x="<<cos(glm::radians(pitch)) * sin(glm::radians(yaw)) << std::endl;
	std::cout <<"y="<< sin(glm::radians(pitch)) << std::endl;
	std::cout <<"z="<< cos(glm::radians(pitch)) * cos(glm::radians(yaw)) << std::endl;*/
	Pitch = pitch;
	Yaw = yaw;
	Right = glm::normalize(glm::cross(Worldup, Forward));
	Up = glm::normalize(glm::cross(Forward, Right));
}
glm::mat4 Camera::GetViewMatrix()
{
	return glm::lookAt(Position, Position - Forward, Worldup);
}
void Camera::UpdateCameraMatrx()
{
	Forward.x = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));
	Forward.y = sin(glm::radians(Pitch));
	Forward.z = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
	Right = glm::normalize(glm::cross(Worldup, Forward));
	Up = glm::normalize(glm::cross(Forward, Right));
}
void Camera::ProcesMouseMoment(float xoffset, float yoffset)
{
	Pitch += xoffset;
	Yaw += yoffset;
	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;
	UpdateCameraMatrx();
}