#include "HealthBar.h"



HealthBar::HealthBar(GLuint tex, char* objFileName, ShaderProgram* sp) : DrawableElement(tex, objFileName, sp)
{
	length = 100.0f;
}

void HealthBar::drawHealthBar(glm::mat4 snailM, float y) {
	M = glm::translate(snailM, glm::vec3(0.0f, y, 0.0f));	
	M = glm::scale(M, glm::vec3(1.0f * length / 100.0f, 0.07f, 0.001f));


	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();
}

void HealthBar::setLength() {
	length -= 20.0;
}

float HealthBar::getLength() {
	return length;
}

HealthBar::~HealthBar()
{
}
