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

class Mountain : public DrawableElement
{
public:
	Mountain(GLuint t, char *objFileName, ShaderProgram* s);
	void drawMountain();

private:
};


#endif