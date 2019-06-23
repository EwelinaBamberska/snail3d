#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>

static float randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


static float getMin(float a, float b, float c) {
	if (a <= b && a <= c)	return a;
	if (b <= a && b <= c)	return b;
	else	return c;
}

static float getMax(float a, float b, float c) {
	if (a >= b && a >= c)	return a;
	if (b >= a && b >= c)	return b;
	else	return c;
}
#endif
