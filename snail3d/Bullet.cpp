#include "Bullet.h"

Bullet::Bullet(GLuint t, char* objFileName, ShaderProgram *sp) : DrawableElement(t, objFileName, sp) {

	char name[] = "models/explosion.obj";
	explosion = new ExplosionEffect(t, name, sp);
}

void Bullet::drawBullet(glm::mat4 bazookaM, float x, float y, double r, double g, double b) {
	M = glm::translate(bazookaM, glm::vec3(-0.05f, 1.2f, 0.0f));
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

	// draw shooted bullet
	M = glm::translate(M, glm::vec3(0.0f, y, x));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	drawTextured(r, g, b);

}


void Bullet::drawExplosion() {
	explosion->draw(M);
}