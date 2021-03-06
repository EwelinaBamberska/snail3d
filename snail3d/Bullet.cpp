#include "Bullet.h"

Bullet::Bullet(GLuint t, char* objFileName, ShaderProgram *sp) : DrawableElement(t, objFileName, sp) {
	char name[] = "models/explosion.obj";
	expl = new ExplosionEffect(t, name, sp);
	resetBullet(glm::mat4(1.0f));
	explosion = false;

	scaling = 2.0f;
	timeOfExplosion = 0.0f;
}

void Bullet::countScaling() {
	scaling += sqrt(sqrt(1.0f + ((timeOfExplosion * 2.0f) / 100.0f)));
}

void Bullet::resetBullet(glm::mat4 bazookaM) {
	setBoxes();
	aabb->setmaxes(aabb->getmaxes()[0] * 0.5f, aabb->getmaxes()[1] * 0.5f, aabb->getmaxes()[2] * 0.5f);
	aabb->setmins(aabb->getmins()[0] * 0.5f, aabb->getmins()[1] * 0.5f, aabb->getmins()[2] * 0.5f);
	aabb->move(-0.05f * 0.5f * 0.2f, 1.2f * 0.5f * 0.2f, 0.0f);
	previousy = previousx = 0.0f;
	M = bazookaM;
	M = glm::translate(M, glm::vec3(-0.05f, 1.2f, 0.0f));
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
	expl->resetM(M);
	scaling = 1.0f;
	timeOfExplosion = 0.0f;	
	explosion = false;
}

void Bullet::drawExplosion() {
	countScaling();
	expl->draw(M, scaling);
	timeOfExplosion += 0.01f;
	if (timeOfExplosion > 5.0f) {
		explosion = false;
	}
}

void Bullet::translateOfM(glm::mat4 snailM) {
	M = snailM;
	M = glm::translate(M, glm::vec3(-0.05f, 1.2f, 0.0f));
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
}

void Bullet::drawBullet(float x, float y, int angle, double r, double g, double b) {

	M = glm::translate(M, glm::vec3(0.0f, (y - previousy) , (x - previousx)));
	if ((y - previousy) * 0.5f * 0.2f < 0.0f) droping = true;
	else droping = false;
	if(angle == 0)
		aabb->moveOn(0.0f, (y - previousy) * 0.5f * 0.2f, (x - previousx) * 0.5f * 0.2f);
	else if (angle == 1){
		aabb->moveOn( - (x - previousx) * 0.5f * 0.2f, (y - previousy) * 0.5f * 0.2f, 0.0f);
	}
	else if (angle == 2) {
		aabb->moveOn(0.0f, (y - previousy) * 0.5f * 0.2f, -(x - previousx) * 0.5f * 0.2f);
	}
	else {
		aabb->moveOn((x - previousx) * 0.5f * 0.2f, (y - previousy) * 0.5f * 0.2f, 0.0f);
	}
	lastymax = aabb->getmaxes()[1];
	lastymin = aabb->getmins()[1];
	previousx = x;
	previousy = y;
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	drawTextured(r, g, b);

}

void Bullet::setExplosion() {
	scaling = 1.0f;
	explosion = true;
}

bool Bullet::getExplosion() {
	return explosion;
}

float Bullet::getlastymax() {
	return lastymax;
}

float Bullet::getlastymin() {
	return lastymin;
}

bool Bullet::getDroping() {
	return droping;
}