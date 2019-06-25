#ifndef EXPLOSIONEFFECT_H
#define EXPLOSIONEFFECT_H

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
#include "OBJloader.h"
#include "AABBObject.h"
#include "allmodels.h"
#include "DrawableElement.h"

class ExplosionEffect : public DrawableElement
{
public:
	ExplosionEffect(GLuint tex, char* objFileName, ShaderProgram* s);
	void draw(glm::mat4 bulletM);

private:
	ShaderProgram* sp;
	glm::mat4 M;
};

#endif

