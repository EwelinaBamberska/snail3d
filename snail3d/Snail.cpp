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
	M = glm::rotate(M, 2*PI * randomFloat(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}


void Snail::moveSnail(float y)
{
	M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f * y)); //Compute model matrix	
	float oldmin = sqrt(pow(aabb->getmins()[1], 2) - pow(aabb->getmins()[2], 2));
	float oldmax = sqrt(pow(aabb->getmaxes()[1], 2) - pow(aabb->getmaxes()[2], 2));
	aabb->setz(aabb->getmins()[2] + cos(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[2] + cos(angleOfSnail * PI / 180) * (y));
	aabb->setx(aabb->getmins()[0] + sin(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[0] + sin(angleOfSnail * PI / 180) * (y));
	xpos += sin(angleOfSnail * PI / 180) * y;
	zpos += cos(angleOfSnail * PI / 180) * y;
}

void Snail::rotateSnail(float x)
{
	angleOfSnail += x / ( PI * 6.25);
	if (angleOfSnail > 360)	angleOfSnail -= 360;
	else if (angleOfSnail < -360)	angleOfSnail += 360;
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

void Snail::setBoxes()
{
    int n_vertices = modelObj->getVNumber() * 4;
    float* verts = modelObj->get_vertices();
    float x1 = verts[0], y1 = verts[1], z1 = verts[2]; //min
    float x2 = verts[0], y2 = verts[1], z2 = verts[2]; //max

    for(int i = 4; i < n_vertices; i+=4)
    {
        if(verts[i] < x1)
            x1 = verts[i];
        else if(verts[i] > x2)
            x2 = verts[i];
        if(verts[i+1] < y1)
            y1 = verts[i+1];
        else if(verts[i+1] > y2)
            y2 = verts[i+1];
        if(verts[i+2] < z1)
            z1 = verts[i+2];
        else if(verts[i+2] > z2)
            z2 = verts[i+2];
    }

    aabb->setmins(x1, y1, z1);
    aabb->setmaxes(x2, y2, z2);
}

bool Snail::getTurn() {
	return turn;
}

void Snail::setTurn(bool t) {
	turn = t;
}

AABBObject* Snail::getaabb()
{
    return aabb;
}



Snail::~Snail()
{
    //dtor
}
