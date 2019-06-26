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
	void setx(float minz, float maxz);
	void sety(float minz);
	float* getmaxes();
	float* getmins();
	bool check_if_collision(AABBObject* object);
	void move(float x, float y, float z);
	void moveOn(float x, float y, float z);
	void setprevious();
	bool getChanged();
	void setChanged(bool b);
	void setyforBullet(float y);
protected:

private:
	float maxes[3];
	float mins[3];
	float pmaxes[3];
	float pmins[3];
	float miny, maxy, minx, maxx, minz, maxz;
	bool changed = false;
};

#endif // AABBOBJECT_H
