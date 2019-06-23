#include "Pointer.h"

Pointer::Pointer(char * objFileName, GLuint tex = NULL) : DrawableElement(tex, objFileName) {}

void Pointer::drawAboveSnail(glm::mat4 snailM) {

	M = glm::translate(snailM, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.3f, 0.3f, 0.3f));

	glUniform4f(spLambert->u("color"), 0.2, 0.7, 1, 1);
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));

	drawSolid();
}