#include "Mountain.h"

Mountain::Mountain(GLuint t, char *objFileName) : DrawableElement(t, objFileName) {
	M = glm::translate(M, glm::vec3(0.0f, translate, 0.0f));
	M = glm::scale(M, glm::vec3(scale, scale, scale));
}

void Mountain::drawMountain() {	
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();
}

bool checkIfInsideTriangle(float x1, float x2, float x3, float z1, float z2, float z3, float xcheck, float zcheck) {
	/*float a1 = countA(x1, x2, z1, z2);
	float b1 = countB(x1, z1, a1);
	float a2 = countA(x1, x3, z1, z3);
	float b2 = countB(x1, z1, a2);
	float a3 = countA(x2, x3, z2, z3);
	float b3 = countB(x2, z2, a3);
	if ((a1 * x1 + z1 + b1) * (a1 * xcheck + zcheck + b1) > 0 && (a2 * x3 + z3 + b2) * (a2 * xcheck + zcheck + b2) > 0 && (a3 * x2 + z2 + b3) * (a3 * xcheck + zcheck + b3) > 0)
		return true;
	return false;*/
	float areaabc = area(x1, z1, x2, z2, x3, z3);
	float areapab = area(x1, z1, x2, z2, xcheck, zcheck);
	float areapbc = area(x1, z1, xcheck, zcheck, x3, z3);
	float areapac = area(xcheck, zcheck, x2, z2, x3, z3);
	if (areaabc == (areapab + areapac + areapbc) ) {
		return true;
	}
	return false;
}

void Mountain::setLastY(float y) {
	lasty = y;
}

float Mountain::getYPosition(float x, float z) {
	//i, i + 1, i + 2, i + 3 -first vertex
	//i + 4, ... , i + 7 - second vertex
	//i + 8, ... , i + 11 - third vertex
	float yToReturn = NULL;
	float* verts = modelObj->get_vertices();
	float beta, alpha, tmpy;
	for (int i = 0; i < modelObj->getVNumber() *4; i += 12) {
		if (checkIfInsideTriangle(verts[i] * scale, verts[i + 4] * scale, verts[i + 8] * scale, verts[i + 2] * scale, verts[i + 6] * scale, verts[i + 10] * scale, x, z)) {
			beta = ((z - verts[i + 2] * scale) * (verts[i + 4] * scale - verts[i] * scale) -
				(x - verts[i] * scale) * (verts[i + 6] * scale - verts[i + 2] * scale)) /
				(verts[i + 10] * scale - verts[i + 2] * scale - (verts[i + 8] * scale - verts[i] * scale) *
				(verts[i + 6] * scale - verts[i + 2] * scale));
			alpha = (x - verts[i] * scale - beta * (verts[i + 8] * scale - verts[i] * scale)) / (verts[i + 4] * scale - verts[i] * scale);
			tmpy = alpha * (verts[i + 5] * scale - verts[i + 1] * scale) + beta * (verts[i + 9] * scale - verts[i + 1] * scale) + verts[i + 1] * scale;
			if (tmpy > getMax(verts[i + 1], verts[i + 5], verts[i + 9]) * scale || isnan(tmpy));
				tmpy = (verts[i + 1] + verts[i + 5] + verts[i + 9]) / 3 * scale;
			if (tmpy < getMin(verts[i + 1], verts[i + 5], verts[i + 9]) * scale)
				tmpy = (verts[i + 1] + verts[i + 5] + verts[i + 9]) / 3 * scale;
			if (!yToReturn) {
				yToReturn = tmpy + translate;
			}
			else if (yToReturn < tmpy + translate) {
				yToReturn = tmpy + translate;
			}
		}
	}
	if (!yToReturn)
		yToReturn = lasty;
	return yToReturn;
}