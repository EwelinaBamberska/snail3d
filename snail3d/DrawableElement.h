#ifndef DRAWABLEELEMENT_H
#define DRAWABLEELEMENT_H

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

class DrawableElement
{
public:
	DrawableElement(GLuint t , char* objFileName);
	void drawSolid();
	void drawTextured();
	void initTextureDrawing(glm::mat4 P, glm::mat4 V);
	void initSolidDrawing(glm::mat4 P, glm::mat4 V);

protected: 
	OBJloader* modelObj;
	glm::mat4 M;
	GLuint tex;
};

#endif
