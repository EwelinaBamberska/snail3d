#include "Bazooka.h"

Bazooka::Bazooka(GLuint bazookaT, GLuint bulletT, char * objFileName, ShaderProgram * sp) : DrawableElement(bazookaT, objFileName, sp) {
	angle = 0.0f;

	char name[] = "models/bullet.obj";
	bullet = new Bullet(bulletT, name, sp);

	shooting = false;
}

void Bazooka::drawBazooka(float z, glm::mat4 snailM) {
	// set position
	angle += z;
	if(angle > 80.0) angle = 80.0;
	if(angle < -20.0) angle = -20.0;
	float angle_conversed = angle * 2 * PI/ 360;
	
	M = glm::translate(snailM, glm::vec3(0.3f, 0.3f, 0.0f));
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
	M = glm::rotate(M, (float)0.5 * PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle_conversed, glm::vec3(-1.0f, 0.0f, 0.0f));

	// draw
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();

	if (!shooting) {
		bullet->drawBullet(M, 0.0f, 0.0f);
	}
}

void Bazooka::startShooting() {
	shooting = true;
	shootedM = M;
}

void Bazooka::moveBullet(float x, float y) {
	bullet->drawBullet(shootedM, x, y);
}

float Bazooka::getAngle() {
	return angle;
}