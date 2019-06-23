#include "Mountain.h"

Mountain::Mountain(GLuint t, char *objFileName) : DrawableElement(t, objFileName) {
	M = glm::translate(M, glm::vec3(0.0f, translate, 0.0f));
	M = glm::scale(M, glm::vec3(scale, scale, scale));
}

void Mountain::drawMountain() {	
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();
}





float Mountain::getYPosition(float x, float z) {
	//i, i + 1, i + 2, i + 3 -first vertex
	//i + 4, ... , i + 7 - second vertex
	//i + 8, ... , i + 11 - third vertex
	float yToReturn = NULL;
	float minx, maxx, minz, maxz;
	float* verts = modelObj->get_vertices();
	float beta, alpha, tmpy;
	for (int i = 0; i < modelObj->getVNumber() *4; i += 12) {
		minx = getMin(verts[i] * scale, verts[i + 4] * scale, verts[i + 8] * scale);
		maxx = getMax(verts[i] * scale, verts[i + 4] * scale, verts[i + 8] * scale);
		minz = getMin(verts[i + 2] * scale, verts[i + 6] * scale, verts[i + 10] * scale);
		maxz = getMax(verts[i + 2] * scale, verts[i + 6] * scale, verts[i + 10] * scale);
		if (minx <= x && maxx >= x && minz <= z && maxz >= z) {
			beta = ((z - verts[i + 2] * scale) * (verts[i + 4] * scale - verts[i] * scale) -
				(x - verts[i] * scale) * (verts[i + 6] * scale - verts[i + 2] * scale)) /
				(verts[i + 10] * scale - verts[i + 2] * scale - (verts[i + 8] * scale - verts[i] * scale) *
				(verts[i + 6] * scale - verts[i + 2] * scale));
			alpha = (x - verts[i] * scale - beta * (verts[i + 8] * scale - verts[i] * scale)) / (verts[i + 4] * scale - verts[i] * scale);
			tmpy = alpha * (verts[i + 5] * scale - verts[i + 1] * scale) + beta * (verts[i + 9] * scale - verts[i + 1] * scale) + verts[i + 1] * scale;
			
			if (tmpy > getMax(verts[i + 1], verts[i + 5], verts[i + 9]) * scale)
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
	return yToReturn;
}