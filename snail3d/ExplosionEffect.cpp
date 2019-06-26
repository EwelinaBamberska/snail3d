#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(GLuint tex, char* objFileName, ShaderProgram* s) : DrawableElement(tex, objFileName, s) {
	sp = s;
	M = glm::mat4(1.0f);
}

void ExplosionEffect::draw(glm::mat4 bulletM, double r, double g, double b) {
	printf("d");
	M = glm::scale(bulletM, glm::vec3(10.0f, 10.0f, 10.0f));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(bulletM));
	drawTextured(r, g, b);

}