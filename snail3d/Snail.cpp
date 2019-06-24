#include "Snail.h"



Snail::Snail(Camera* c, char* objFileName, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex, bool tur) : DrawableElement(snailTex, objFileName)
{
    camera = c;
    aabb = new AABBObject();

	char name[] = "models/bazooka.obj";
	bazooka = new Bazooka(bazookaTex, bulletTex, name);
	turn = tur;
}

void Snail::setRandomCoords(int i) {
	float xcoord = -4.0f + randomFloat(0.0f, 8.0f);
	float ycoord = -4.0f + randomFloat(0.0f, 8.0f);

	M = glm::translate(M, glm::vec3(xcoord, 0.0f, ycoord));
	float randomAngle = 2 * PI * randomFloat(0.0f, 1.0f);
	M = glm::rotate(M, randomAngle, glm::vec3(0.0f, 1.0f, 0.0f));
	angleOfSnail +=  - randomAngle * PI * 180.0f;
}


void Snail::moveSnail(float y)
{
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f * y)); //Compute model matrix	
	aabb->setz(aabb->getmins()[2] + cos(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[2] + cos(angleOfSnail * PI / 180) * (y));
	aabb->setx(aabb->getmins()[0] + sin(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[0] + sin(angleOfSnail * PI / 180) * (y));
	xpos += sin(angleOfSnail * PI / 180) * y;
	zpos += cos(angleOfSnail * PI / 180) * y;
}

void Snail::rotateSnail(float x)
{
	angleOfSnail += x / ( PI * 6.25);
	if (angleOfSnail > 360)	angleOfSnail -= 360;
	else if (angleOfSnail < 0)	angleOfSnail += 360;
	x = x / ( PI * 360.0);
	M = glm::rotate(M, x, glm::vec3(0.0f, -1.0f, 0.0f));
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
void Snail::draw( float z)
{
	//z = 0.1 * z;
	z = turn == true ? 0.1 * z : 0;
	glm::mat4 tmpM = glm::translate(M, glm::vec3(0.0f, ypos, 0.0f));
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(tmpM));

	// for solids
	//initSolidDrawing(camera->getP(), camera->getV());

	initTextureDrawing(camera->getP(), camera->getV());
	drawTextured();
	bazooka->drawBazooka(z, M);

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
