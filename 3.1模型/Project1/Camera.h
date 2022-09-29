#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{
public:
	Camera(glm::vec3 position,glm::vec3 target,glm::vec3 worldup);
	Camera(glm::vec3 position, float pitch, float yaw, glm::vec3 worldup);
	
	glm::vec3 Position;
	glm::vec3 Worldup;
	glm::vec3 Right;
	glm::vec3 Forward;
	glm::vec3 Up;
	float Pitch;
	float Yaw;
	glm::mat4 GetMatrixView();

	void ProcesMouseMoment(float xoffset, float yoffset);
private:
	void UpdateCameraMatrx();
};
