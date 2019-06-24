#include "Snail.h"



Snail::Snail(Camera* c, char* objFileName, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex, bool tur, ShaderProgram *sp) : DrawableElement(snailTex, objFileName, sp)
{
	camera = c;

	char pointerName[] = "models/pointer.obj";
	pointer = new Pointer(pointerName, NULL, sp);

	char name[] = "models/bazooka.obj";
	bazooka = new Bazooka(bazookaTex, bulletTex, name, sp);
	turn = tur;
}

void Snail::setRandomCoords(int i) {
	float xcoord = -4.0f + randomFloat(0.0f, 8.0f);
	float ycoord = -4.0f + randomFloat(0.0f, 8.0f);
	printf("xcord %f %f\n", xcoord, ycoord);
	aabb->move(xcoord, 0.0f, ycoord);
	bazooka->getBullet()->getaabb()->move(xcoord, 0.0f, ycoord);
	printf("min %f %f\n", aabb->getmins()[0], aabb->getmins()[2]);
	M = glm::translate(M, glm::vec3(xcoord, 0.0f, ycoord));
	//float randomAngle = 2 * PI * randomFloat(0.0f, 1.0f);
	//M = glm::rotate(M, randomAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	//angleOfSnail +=  randomAngle * PI * 180.0f;
}


void Snail::moveSnail(float y)
{
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f * y)); //Compute model matrix	
	//aabb->setz(cos(angleOfSnail * PI / 180) * (y),  cos(angleOfSnail * PI / 180) * (y));
	//aabb->setx(aabb->getmins()[0] + sin(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[0] + sin(angleOfSnail * PI / 180) * (y));
	
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
	//printf("X min %f max %f \t Z min %f, max %f\n", aabb->getmins()[0], aabb->getmaxes()[0], aabb->getmins()[2], aabb->getmaxes()[2]);

	xpos += sin(angleOfSnail * PI / 180) * y;
	zpos += cos(angleOfSnail * PI / 180) * y;
}

void Snail::rotateSnail(int x)
{
	//angleOfSnail += (float)x;
	//printf("OBRÓT: %f\n", angleOfSnail);
	//if (angleOfSnail > 2 * PI)	angleOfSnail = 0.0f;
	//else if (angleOfSnail < 0.0f)	angleOfSnail = 2 * PI;
	//x = x / ( PI * 360.0);
	angle += x;
	if (angle > 3)	angle = 0;
	else if (angle < 0) angle = 3;
	M = glm::rotate(M, PI / 2 * (float) x, glm::vec3(0.0f, -1.0f, 0.0f));

}

/*
void Snail::moveSnail(float x, float y, float z)
{
	x = 0.002f * x;
	y = 0.001f * y;
	rotateSnail(x, y, z);

	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f * y)); //Compute model matrix
	aabb->setz(aabb->getmins()[2] + 1.0f * y, aabb->getmaxes()[2] + 1.0f * y);
}

void Snail::rotateSnail(float x, float y, float z)
{
    M = glm::rotate(M, x, glm::vec3(0.0f, -1.0f, 0.0f));
}
*/
void Snail::draw(float z)
{
	//z = 0.1 * z;
	z = turn == true ? 0.1 * z : 0;


	// for solids
	//initSolidDrawing(camera->getP(), camera->getV());

	if (turn == true) {
		initSolidDrawing(camera->getP(), camera->getV());
		pointer->drawAboveSnail(M);
	}
	//glm::mat4 tmpM = glm::translate(M, glm::vec3()
	initTextureDrawing(camera->getP(), camera->getV());
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();
	bazooka->drawBazooka(z, M);

	if (shooting == true) {
		countShootingTrajectory();
	}
}


void Snail::shootBullet(float strength) {
	shooting = true;
	yShooting = 0.0f;
	xShooting = 0.0f;
	angleShooting = bazooka->getAngle() + 10.0f;
	timeShooting = 0.0f;
	speedShooting = log(strength) / log(2) * 4;
	printf("angle: %f ----- speed: %f ---- cosinus: %f, ----- sinus: %f\n", angleShooting, speedShooting, cos(angleShooting * PI / 180), sin(angleShooting * PI / 180));
	bazooka->startShooting();
}

void Snail::countShootingTrajectory() {
	xShooting = speedShooting * timeShooting * cos(angleShooting * PI / 180) * 1.8f;
	yShooting = speedShooting * timeShooting * sin(angleShooting * PI / 180) + 3.0f - 0.5f * 9.806f * pow(timeShooting, 2);
	timeShooting += 0.001f;

	bazooka->moveBullet(xShooting, yShooting);
}

void Snail::setYPos(float y) {
	ypos = y;
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