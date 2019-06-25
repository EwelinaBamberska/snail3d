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
#include "DrawableElement.h"

class Bullet : public DrawableElement
{
public:
	Bullet(GLuint t, char* objFileName, ShaderProgram* sp);
	void drawBullet(float x, float y, int angle);
	//void drawShootedBullet(glm::mat4 bazookaM, float x, float y);
	void resetBullet(glm::mat4 M);
	void translateOfM(glm::mat4 snailM);

private:
	float previousx, previousy;
};

#endif