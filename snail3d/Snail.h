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

#include <iostream>
class Snail
{
public:
	Snail(Camera* c, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex);// ShaderProgram* s);
	virtual ~Snail();
	void moveSnail(float angle_x, float angle_y, float move_up);
	void draw(float z);
	void rotateSnail(float angle_x, float angly_y, float z);
	void setBoxes();
	//void drawBazooka(float z);
	AABBObject* getaabb();


protected:

private:
	Bazooka* bazooka;
	OBJloader* snailObj;
	glm::mat4 M;
	Camera* camera;
	void drawSolid();
	AABBObject* aabb;
	GLuint tex;


};

#endif
