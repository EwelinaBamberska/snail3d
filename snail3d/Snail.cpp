#include "Snail.h"



Snail::Snail(Camera* c, char* objFileName, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex, bool tur, ShaderProgram *sp, GLuint blueTex, GLuint redTex, Mountain* m) : DrawableElement(snailTex, objFileName, sp)
{
	camera = c;
	mountain = m;

	char pointerName[] = "models/pointer.obj";
	pointer = new Pointer(pointerName, blueTex, sp);

	char name[] = "models/bazooka.obj";
	bazooka = new Bazooka(bazookaTex, bulletTex, name, sp);
	turn = tur;
	char healthName[] = "models/strengthbar.obj";
	healthBar = new HealthBar(blueTex, healthName, sp);
	actualLife = new HealthBar(redTex, healthName, sp);
	initialFlashTime = 5.0f;
	flashTime = 0.0f;
	lastY = 0.0f;

	wind = 0.0f;

}

void Snail::setRandomCoords(int i) {
	float xcoord = -4.0f + randomFloat(0.0f, 8.0f);
	float ycoord = -4.0f + randomFloat(0.0f, 8.0f);
	aabb->move(xcoord, 0.0f, ycoord);
	
	M = glm::translate(M, glm::vec3(xcoord, 0.0f, ycoord));
	bazooka->translateBazooka(xcoord, ycoord);
	bazooka->getBullet()->resetBullet(bazooka->getM());
	bazooka->getBullet()->getaabb()->moveOn(xcoord * 5.0f, 0.0f, ycoord * 5.0f);
}


void Snail::moveSnail(float y)
{
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f * y)); //Compute model matrix	

	if (angle == 0) {
		aabb->setz(y, y);
		bazooka->getBullet()->getaabb()->setz(y, y);
	}
	else if (angle == 3) {
		aabb->setx(y, y);
		bazooka->getBullet()->getaabb()->setx(y, y);
	}
	else if (angle == 2) {
		aabb->setz(-y, -y);
		bazooka->getBullet()->getaabb()->setz(-y, -y);
	}
	else {
		aabb->setx(-y, -y);
		bazooka->getBullet()->getaabb()->setx(-y, -y);
	}

	xpos += sin(angleOfSnail * PI / 180) * y;
	zpos += cos(angleOfSnail * PI / 180) * y;
}

void Snail::rotateSnail(int x)
{
	angle += x;
	if (angle > 3)	angle = 0;
	else if (angle < 0) angle = 3;
	M = glm::rotate(M, PI / 2 * (float)x, glm::vec3(0.0f, -1.0f, 0.0f));
}

void Snail::draw(float z, double r, double g, double b)
{
	z = turn == true ? 0.1 * z : 0;
	decreaseFlashTime();

	
	initTextureDrawing(camera->getP(), camera->getV());
	glm::mat4 M1 = glm::translate(M, glm::vec3(0.0f, lastY, 0.0f));
	if (turn == true) {
		initSolidDrawing(camera->getP(), camera->getV());
		pointer->drawAboveSnail(M1, r, g, b);
	}
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M1));
	
	drawTextured(r, g, b);
	bazooka->drawBazooka(z, M1, angle, r, g, b);
	healthBar->drawHealthBar(M1, 2.0f);
	actualLife->drawHealthBar(M1, 2.2f);
	if (shooting == true || bazooka->getBullet()->getExplosion()) {
		countShootingTrajectory(r, g, b);
	}

}


void Snail::shootBullet(float strength) {
	shooting = true;
	yShooting = 0.0f;
	xShooting = 0.0f;
	angleShooting = bazooka->getAngle() + 10.0f;
	timeShooting = 0.0f;
	speedShooting = log(strength) / log(2) * 6;

	wind = randomFloat(0.0f, 3.0f) - 1.5f;

	bazooka->startShooting();
	bazooka->getBullet()->resetBullet(bazooka->getM());
	bazooka->getBullet()->getaabb()->moveOn((aabb->getmins()[0] + aabb->getmaxes()[0]) / 2, (aabb->getmins()[1] + aabb->getmaxes()[1]) / 2, (aabb->getmins()[2] + aabb->getmaxes()[2]) / 2);
}

void Snail::countShootingTrajectory(double r, double g, double b) {

	xShooting = speedShooting * timeShooting * cos(angleShooting * PI / 180) * 1.0f + wind;
	yShooting = speedShooting * timeShooting * sin(angleShooting * PI / 180) + 0.0f - 0.5f * 9.806f * pow(timeShooting, 2);
	timeShooting += 0.005f;
	bazooka->moveBullet(xShooting, yShooting, angle, r, g, b);
	if (timeShooting > 1.0f && bazooka->getBullet()->getDroping() || bazooka->getBullet()->getDroping() && yShooting < mountain->getYPosition(bazooka->getBullet()->getaabb()->getmaxes()[0], bazooka->getBullet()->getaabb()->getmaxes()[2], angle, bazooka->getBullet()->getlastymax()) &&
		yShooting > mountain->getYPosition(bazooka->getBullet()->getaabb()->getmins()[0], bazooka->getBullet()->getaabb()->getmins()[2], angle, bazooka->getBullet()->getlastymin())
		|| yShooting < -0.4f) {
		shooting = false;
		bazooka->endShooting();
		flashTime = initialFlashTime;
		bazooka->getBullet()->resetBullet(bazooka->getM());
		stop = true;
	}
}

void Snail::setYPos(float y) {
	ypos = y;
}

void Snail::setShooting() {
	shooting = false;
}


bool Snail::getTurn() {
	return turn;
}

void Snail::setTurn(bool t) {
	turn = t;
}


float Snail::getAngle() {
	return angleOfSnail;
}

Snail::~Snail()
{
	//dtor
}

Bazooka* Snail::getBazooka() {
	return bazooka;
}

bool Snail::getShooting() {
	return shooting;
}

void Snail::loseLife() {
	actualLife->setLength();
	if (actualLife->getLength() == 0.0f) {
		ifLive = false;
	}
}

bool Snail::getIfLive() {
	return ifLive;
}

float Snail::getTimeShooting() {
	return timeShooting;
}


void Snail::decreaseFlashTime() {
	if (flashTime > 0.0f) flashTime -= 0.01f;
}

RGBflashLight Snail::getRGB() {
	RGBflashLight rgb;

	if (flashTime <= 0.0f) {
		rgb.r = 0;
		rgb.g = 0;
		rgb.b = 0;
	}
	else if (flashTime <= initialFlashTime / 2.0) {
		rgb.r = (flashTime / (initialFlashTime / 2.0));
		rgb.g = (0.8 * flashTime / (initialFlashTime / 2.0));
		rgb.b = 0;
	}
	else {
		rgb.r = 1;
		rgb.g = 0.8;
		rgb.b = 0;
	}

	return rgb;
}

void Snail::setLastY(float y) {
	lastY = y;
}

float Snail::getLasty() {
	return lastY;
}

void Snail::setStop() {
	stop = false;
}

bool Snail::getStop() {
	return stop;
}
