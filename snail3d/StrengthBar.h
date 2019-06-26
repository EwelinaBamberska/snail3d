#ifndef STRENGTHBAR_H
#define STRENGTHBAR_H

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
//#include "myCube.h"


class StrengthBar : public DrawableElement
{
public:
	StrengthBar(Camera* c, ShaderProgram* sp, GLuint tex, char* objFileName);
	virtual ~StrengthBar();
	void loadCube();
	void draw(float s);
	void setLength(float l);
	float getLength();
	float getMaxLength();

protected:

private:
	//glm::mat4 M;
	float length;
	float maxLength;
	Camera *camera;
	//ShaderProgram* sp;
};

#endif // STRENGTHBAR_H
