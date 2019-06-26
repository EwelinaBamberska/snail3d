#include "Bullet.h"

Bullet::Bullet(GLuint t, char* objFileName, ShaderProgram *sp) : DrawableElement(t, objFileName, sp) {
	//setBoxes();
	/*aabb->setmaxes(aabb->getmaxes()[0] * 0.5f, aabb->getmaxes()[1] * 0.5f, aabb->getmaxes()[2] * 0.5f);
	aabb->setmins(aabb->getmins()[0] * 0.5f, aabb->getmins()[1] * 0.5f, aabb->getmins()[2] * 0.5f);
	aabb->move(-0.05f * 0.5f, 1.2f * 0.5f, 0.0f);
	previousy = previousx = 0.0f;*/
	resetBullet(glm::mat4(1.0f));
	explosion = false;
}

void Bullet::countScaling() {
	scaling = timeOfExplosion * 2.0f;//(5.0f - (5.0f - timeOfExplosion / 2));
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

	scaling = 1.0f;
	timeOfExplosion = 0.0f;	
	explosion = false;
}

void Bullet::drawExplosion() {
	M = glm::scale(M, glm::vec3(scaling, scaling, scaling));
	printf("EKSPLOZJA\n");
	timeOfExplosion += 0.1f;
	if (timeOfExplosion > 5.0f) {
		explosion = false;
	}
}

//void Bullet::drawBullet(glm::mat4 bazookaM, float x, float y, int angle) { }

void Bullet::translateOfM(glm::mat4 snailM) {
	M = snailM;
	M = glm::translate(M, glm::vec3(-0.05f, 1.2f, 0.0f));

	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));

}

void Bullet::drawBullet(float x, float y, int angle) {

	M = glm::translate(M, glm::vec3(0.0f, (y - previousy) , (x - previousx)));
	//printf("%f, %f\n", x, y);

	// draw shooted bullet
	//printf("BULLET X min %f max %F\t Y min %f max %f\t Z min %f max %f\n", aabb->getmins()[0], aabb->getmaxes()[0], aabb->getmins()[1], aabb->getmaxes()[1], aabb->getmins()[2], aabb->getmaxes()[2]);
	/*if (aabb->getChanged()) {
		aabb->setprevious();
		aabb->setChanged(false);
	}*/
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
	//printf("Previous %f x %f Roznica %f\n", previousx, x, x - previousx);
	previousx = x;
	previousy = y;
	//if (y != 0.0f || x != 0.0f)
		//aabb->setChanged(true);
	//printf("%f\n", y);
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	drawTextured();

}

void Bullet::setExplosion() {
	explosion = true;
}

bool Bullet::getExplosion() {
	return explosion;
}