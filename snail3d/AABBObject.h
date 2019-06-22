#ifndef AABBOBJECT_H
#define AABBOBJECT_H


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

class AABBObject
{
public:
	AABBObject();
	virtual ~AABBObject();
	void setmaxes(float x, float y, float z);
	void setmins(float x, float y, float z);
	void setz(float minz, float maxz);
	float* getmaxes();
	float* getmins();
	bool check_if_collision(AABBObject* object);
protected:

private:
	float maxes[3];
	float mins[3];
};

#endif // AABBOBJECT_H
