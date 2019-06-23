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

class Snail : public DrawableElement
{
public:
	Snail(Camera* c, char* objFileName, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex, bool turn);
	virtual ~Snail();
	void moveSnail(float angle_x, float angle_y, float move_up);
	void draw(float z);
	void rotateSnail(float angle_x, float angly_y, float z);
	void setBoxes();
	AABBObject* getaabb();
	bool getTurn();
	void setTurn(bool t);
	void setRandomCoords(int i);

protected:

private:
	Bazooka* bazooka;
	Camera* camera;
	AABBObject* aabb;
	bool turn;
};

#endif
