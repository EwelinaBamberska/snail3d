#ifndef BAZOOKA_H
#define BAZOOKA_H

#include <stdlib.h>
#include <stdio.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "shaderprogram.h"

#include "allmodels.h"
#include "Bullet.h"
#include "OBJloader.h"


class Bazooka : public DrawableElement
{
public:
	Bazooka(GLuint bazookaT, GLuint bulletT, char * objFileName);
	void drawBazooka(float z, glm::mat4 M);
	//void drawSolid();

private:
	float angle;
	//glm::mat4 M;
	//OBJloader* bazookaObj;
	Bullet* bullet;
	//GLuint tex;
};

#endif
