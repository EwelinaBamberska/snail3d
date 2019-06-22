#include "Bullet.h"

Bullet::Bullet(GLuint t, char* objFileName) : DrawableElement(t, objFileName) {

}

void Bullet::drawBullet(glm::mat4 bazookaM) {
	M = glm::translate(bazookaM, glm::vec3(-0.05f, 1.2f, 0.6f));
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

	drawTextured();

}