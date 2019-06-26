#include "Pointer.h"

Pointer::Pointer(char * objFileName, GLuint tex, ShaderProgram* sp) : DrawableElement(tex, objFileName, sp) {}

void Pointer::drawAboveSnail(glm::mat4 snailM, double r, double g, double b) {

	M = glm::translate(snailM, glm::vec3(0.0f, 1.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.3f, 0.3f, 0.3f));

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	drawTextured(r, g, b);
}