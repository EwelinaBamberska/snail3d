#ifndef MOUNTAIN_H
#define MOUNTAIN_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"

#include "allmodels.h"
#include "OBJloader.h"

class Mountain
{
public:
	Mountain(GLuint t);
	void drawMountain();
	void drawSolid();

private:
	OBJloader*  mountainObj;
	glm::mat4 M;
	GLuint tex;
};


#endif