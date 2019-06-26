#include "ExplosionEffect.h"

ExplosionEffect::ExplosionEffect(GLuint tex, char* objFileName, ShaderProgram* s) : DrawableElement(tex, objFileName, s) {
	sp = s;
	M = glm::mat4(1.0f);
}

void ExplosionEffect::resetM(glm::mat4 bulletM) {
	M = bulletM;
}

void ExplosionEffect::draw(glm::mat4 bulletM, float scale) {
	M = glm::scale(bulletM, glm::vec3(scale, scale, scale));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();

}