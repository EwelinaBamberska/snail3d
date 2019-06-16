#pragma once
#include "constants.h"

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "lodepng.h"
#include "allmodels.h"
#include "Camera.h"

class Bazooka
{
public:
	Bazooka(Camera* c);
	void drawBazooka(float z, glm::mat4 M);
	~Bazooka();
private:
	float angleOfBazooka = 0;
	glm::mat4 bazookaM;
	Camera* camera;
};

