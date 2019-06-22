#include "Camera.h"

Camera::Camera()
{
	V = glm::lookAt(
		glm::vec3(0.0f, 3.0f, -5.0f),
		glm::vec3(0.0f, 0.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)); //compute view matrix
	P = glm::perspective(50.0f*PI / 180.0f, 1.0f, 1.0f, 50.0f);
	//ctor
}

glm::mat4 Camera::getP() {
	return P;
}

glm::mat4 Camera::getV() {
	return V;
}

void Camera::moveCamera(float x, float y) {
}

Camera::~Camera()
{
	//dtor
}
