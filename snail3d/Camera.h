#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "constants.h"
class Camera
{
public:
	Camera();
	virtual ~Camera();
	glm::mat4 getV();
	glm::mat4 getP();
	void moveCamera(float x, float y);

protected:

private:
	glm::mat4 V;
	glm::mat4 P;
};

#endif // CAMERA_H
