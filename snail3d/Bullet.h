#ifndef BULLET_H
#define BULLET_H

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

class Bullet
{
public:
	Bullet(GLuint t);
	void drawBullet(glm::mat4 M);
	void drawSolid();

private:
	OBJloader* bulletObj;
	glm::mat4 M;
	GLuint tex;
};

#endif