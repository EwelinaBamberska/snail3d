#include "AABBObject.h"

AABBObject::AABBObject()
{
	//ctor
}

bool AABBObject::check_if_collision(AABBObject* object) {
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
}

void AABBObject::setmins(float x, float y, float z) {
	mins[0] = x;
	mins[1] = y;
	mins[2] = z;
}

void AABBObject::setz(float minz, float maxz) {
	maxes[2] = maxz;
	mins[2] = minz;
}

float* AABBObject::getmaxes() {
	return maxes;
}

float* AABBObject::getmins() {
	return mins;
}

AABBObject::~AABBObject()
{
	//dtor
}