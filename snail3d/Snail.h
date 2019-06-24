#ifndef SNAIL_H
#define SNAIL_H

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
#include "allmodels.h"
#include "AABBObject.h"
#include "Bazooka.h"
#include "Mountain.h"
#include "DrawableElement.h"
#include "Utils.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "Pointer.h"

class Snail : public DrawableElement
{
public:
	Snail(Camera* c, char* objFileName, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex, bool turn, ShaderProgram* sp);
	virtual ~Snail();
	void moveSnail(float x);
	void draw( float z);
	void rotateSnail(int angle);
	bool getTurn();
	void setTurn(bool t);
	void setRandomCoords(int i);
	void setYPos(float newy);
	float getAngle();

	void shootBullet(float strength);
	void countShootingTrajectory(); // to do
	Bazooka* getBazooka();
	bool getShooting();

protected:

private:
	Bazooka* bazooka;
	Camera* camera;
	bool turn;
	float angleOfSnail = 0.0f;
	float xpos = 0.0f, zpos = 0.0f;
	float ypos;
	float xcoord, ycoord;
	glm::mat4 tmpM;

	Pointer* pointer;
	float HP;

	// shooting variables
	bool shooting;
	float yShooting;
	float xShooting;
	float angleShooting;
	float timeShooting;
	float speedShooting;
	int angle = 0;
};

#endif
