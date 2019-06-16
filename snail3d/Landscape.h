#pragma once
#include "OBJloader.h"
#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "lodepng.h"
#include "Camera.h"
class Landscape
{
public:
	Landscape(Camera* c, GLuint tex);
	~Landscape();
	void drawSolid();
private:
	OBJloader* landscapeObj;
	glm::mat4 M;
	Camera* camera;
	GLuint tex;
};

