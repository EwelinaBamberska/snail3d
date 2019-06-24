#include "Bullet.h"

Bullet::Bullet(GLuint t, char* objFileName, ShaderProgram *sp) : DrawableElement(t, objFileName, sp) {
	setBoxes();
	aabb->setmaxes(aabb->getmaxes()[0] * 0.5f, aabb->getmaxes()[1] * 0.5f, aabb->getmaxes()[2] * 0.5f);
	aabb->setmins(aabb->getmins()[0] * 0.5f, aabb->getmins()[1] * 0.5f, aabb->getmins()[2] * 0.5f);
	aabb->move(-0.05f * 0.5f, 1.2f * 0.5f, 0.0f);

}

void Bullet::drawBullet(glm::mat4 bazookaM, float x, float y) {
	M = glm::translate(bazookaM, glm::vec3(-0.05f, 1.2f, 0.0f));
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

	// draw shooted bullet
	M = glm::translate(M, glm::vec3(0.0f, y, x));
	/*if (aabb->getChanged()) {
		aabb->setprevious();
		aabb->setChanged(false);
	}*/
	//aabb->move(0.0f, y * 0.5f, x * 0.5f);
	//if (y != 0.0f || x != 0.0f)
		//aabb->setChanged(true);
	//printf("%f\n", y);
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	drawTextured();

}