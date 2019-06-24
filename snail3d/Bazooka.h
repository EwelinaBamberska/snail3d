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
	Bazooka(GLuint bazookaT, GLuint bulletT, char * objFileName, ShaderProgram *sp);
	void drawBazooka(float z, glm::mat4 M);
	float getAngle();
	void moveBullet(float x, float y);
	void startShooting();
	Bullet* getBullet();

private:
	float angle;
	Bullet* bullet;
	bool shooting;
	glm::mat4 shootedM;
};

#endif
