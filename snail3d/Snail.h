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
#include "math.h"
#include "Bazooka.h"

class Snail
{
public:
	Snail(Camera* c, GLuint t);// ShaderProgram* s);
	virtual ~Snail();
	void moveSnail(float angle_x);
	void draw();
	void rotateSnail(float z);
	void setBoxes();
	void drawBazooka(float z);
	AABBObject* getaabb();
	glm::mat4 getM();
	Bazooka* getBazooka();


protected:

private:
	OBJloader* snailObj;
	float angleOfBazooka = 0;
	glm::mat4 M;
	glm::mat4 bazookaM;
	Camera* camera;
	void drawSolid();
	AABBObject* aabb;
	float angleOfSnail = 0;
	GLuint tex;
	Bazooka* bazooka;
};

#endif // SNAIL_H
