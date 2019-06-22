#include "Mountain.h"

Mountain::Mountain(GLuint t, char *objFileName) : DrawableElement(t, objFileName) {
	M = glm::translate(M, glm::vec3(0.0f, -1.5f, 0.0f));
}

void Mountain::drawMountain() {	
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 1.0f));
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();
}