#ifndef POINTER_H
#define POINTER_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"
#include "lodepng.h"

#include "DrawableElement.h"


class Pointer : public DrawableElement
{
public:
	Pointer(char *objFileName, GLuint tex);
	void drawAboveSnail(glm::mat4 M);
};

#endif