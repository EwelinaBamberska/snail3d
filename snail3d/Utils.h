#ifndef UTILS_H
#define UTILS_H

#include <stdlib.h>
#include <stdio.h>


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

static float countA(float x1, float x2, float z1, float z2) {
	return (z2 - z1) / (x2 - x1);
}

static float countB(float x1, float z1, float a) {
	return z1 - a * x1;
}

static float area(float x1, float y1, float x2, float y2, float x3, float y3)
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0);
}

static float randomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

#endif
