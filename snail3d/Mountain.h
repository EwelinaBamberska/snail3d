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
#include "DrawableElement.h"
#include "Utils.h"

class Mountain : public DrawableElement
{
public:
	Mountain(GLuint t, char *objFileName, ShaderProgram* sp);
	void drawMountain(double r, double g, double b);
	float getYPosition(float x, float z, int alpha, float lasty);

private:
	float scale = 1.0f;
	float translate = -2.0f;
};


#endif