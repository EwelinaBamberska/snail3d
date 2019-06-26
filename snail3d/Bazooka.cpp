#include "Bazooka.h"

Bazooka::Bazooka(GLuint bazookaT, GLuint bulletT, char * objFileName, ShaderProgram * sp) : DrawableElement(bazookaT, objFileName, sp) {
	angle = 0.0f;

	char name[] = "models/bullet.obj";
	bullet = new Bullet(bulletT, name, sp);
	bullet->resetBullet(M);
	//bullet->setBoxes();
	shooting = false;
}

void Bazooka::drawBazooka(float z, glm::mat4 snailM, int angl) {
	// set position
	angle += z;
	if (angle > 80.0) angle = 80.0;
	if (angle < -20.0) angle = -20.0;
	float angle_conversed = angle * 2 * PI / 360;

	M = glm::translate(snailM, glm::vec3(0.3f, 0.3f, 0.0f));
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
	M = glm::rotate(M, (float)0.5 * PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle_conversed, glm::vec3(-1.0f, 0.0f, 0.0f));

	// draw
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();

	if (!shooting) {
		bullet->translateOfM(M);
		bullet->drawBullet( 0.0f, 0.0f, angl);
	}
}

glm::mat4 Bazooka::getM() {
	return M;
}

void Bazooka::startShooting() {
	shooting = true;
	shootedM = M;

}

void Bazooka::moveBullet(float x, float y, int angle) {
	//printf("BAZO %d\n", bullet->getExplosion());
	if (bullet->getExplosion()) {
		bullet->drawExplosion();

	}
	bullet->drawBullet(x, y, angle);
}

float Bazooka::getAngle() {
	return angle;
}

Bullet* Bazooka::getBullet() {
	return bullet;
}

void Bazooka::translateBazooka(float x, float y) {
	M = glm::translate(M, glm::vec3(x, 0.0f, y));
	M = glm::translate(M, glm::vec3(0.3f, 0.3f, 0.0f));
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
}

void Bazooka::endShooting() {
	shooting = false;
}