#include "AABBObject.h"

AABBObject::AABBObject()
{
	//ctor
}

bool AABBObject::check_if_collision(AABBObject* object) {
	//printf("Snail: x  %f y %f z %f\n", object->getmins()[0], object->getmins()[1], object->getmins()[2]);
	//printf("BULLET: x %f y %f z %f\n", mins[0], mins[1], mins[2]);
	/*if (mins[0] <= object->getmaxes()[0] && maxes[0] >= object->getmins()[0]) printf("X sie mieszcza\n");
	if (mins[1] <= object->getmaxes()[1] && maxes[1] >= object->getmins()[1]) printf("Y teü\n");
	if (mins[2] <= object->getmaxes()[2] && maxes[2] >= object->getmins()[2]) printf("Z\n");*/
	if (mins[0] <= object->getmaxes()[0] && maxes[0] >= object->getmins()[0] &&
		mins[1] <= object->getmaxes()[1] && maxes[1] >= object->getmins()[1] &&
		mins[2] <= object->getmaxes()[2] && maxes[2] >= object->getmins()[2])
		return true;
	return false;
}

void AABBObject::setmaxes(float x, float y, float z) {
	maxes[0] = x;
	maxes[1] = y;
	maxes[2] = z;
	maxy = y;
	maxx = x;
	maxz = z;
}

void AABBObject::setmins(float x, float y, float z) {
	mins[0] = x;
	mins[1] = y;
	mins[2] = z;
	miny = y;
	minz = z;
	minx = x;
}

void AABBObject::setz(float minz, float maxz) {
	maxes[2] += maxz;
	mins[2] += minz;
}

void AABBObject::setx(float minx, float maxx) {
	maxes[0] += maxx;
	mins[0] += minx;
}

void AABBObject::sety(float y1) {
	maxes[1] = maxy + y1;
	mins[1] = miny + y1;
}

float* AABBObject::getmaxes() {
	return maxes;
}

float* AABBObject::getmins() {
	return mins;
}

void AABBObject::move(float x, float y, float z) {
	pmins[0] = mins[0] = x + minx;
	pmaxes[0] = maxes[0] = x + maxx;
	pmins[1] = mins[1] = y + miny;
	pmaxes[1] = maxes[1] = y + maxy;
	pmins[2] = mins[2] = z + minz;
	pmaxes[2] = maxes[2] = z + maxz;
	//printf("X min %f max %f Y min %f max %f Z min %f max %f\n", mins[0], maxes[0], mins[1], maxes[1], mins[2], maxes[2]);
}

void AABBObject::moveOn(float x, float y, float z) {
	mins[0] = mins[0] + x;
	maxes[0] = maxes[0] + x;
	mins[1] += y;
	maxes[1] += y;
	mins[2] += z;
	maxes[2] += z;
	//printf("X min %f max %f Y min %f max %f Z min %f max %f\n", mins[0], maxes[0], mins[1], maxes[1], mins[2], maxes[2]);

}

void AABBObject::setprevious() {
	for (int i = 0; i < 3; i++) {
		maxes[i] = pmaxes[i];
		mins[i] = pmins[i];
	}
}

AABBObject::~AABBObject()
{
	//dtor
}


void AABBObject::setChanged(bool b) {
	changed = b;
}

bool AABBObject::getChanged() {
	return changed;
}