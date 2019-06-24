#include "Snail.h"



Snail::Snail(Camera* c, char* objFileName, GLuint snailTex, GLuint bazookaTex, GLuint bulletTex, bool tur, ShaderProgram *s, GLuint pointerTex) : DrawableElement(snailTex, objFileName, s)
{
    camera = c;
    aabb = new AABBObject();
	HP = 1.0f;

	char pointerName[] = "models/pointer.obj";
	pointer = new Pointer(pointerName, pointerTex, sp);

	char name[] = "models/bazooka.obj";
	bazooka = new Bazooka(bazookaTex, bulletTex, name, sp);
	turn = tur;

	flashTime = 0.0f;
	initialFlashTime = 5.0f;
}

void Snail::setRandomCoords(int i) {
	//srand(time(NULL));

	float xcoord = -4.0f + randomFloat(0.0f, 8.0f);
	float ycoord = -4.0f + randomFloat(0.0f, 8.0f);

	M = glm::translate(M, glm::vec3(xcoord, 0.0f, ycoord));
	M = glm::rotate(M, 2*PI * randomFloat(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}

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

void Snail::draw(float z, double r, double g, double b)
{
	//z = 0.1 * z;
	z = turn == true ? 0.1 * z : 0;
	decreaseFlashTime();

	// for solids
	//initSolidDrawing(camera->getP(), camera->getV());

	if (turn == true) {
		initSolidDrawing(camera->getP(), camera->getV());
		pointer->drawAboveSnail(M, r, g, b);
	}

	initTextureDrawing(camera->getP(), camera->getV());
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	drawTextured(r, g, b);
	bazooka->drawBazooka(z, M, r, g, b);
	
	if (shooting == true) {
		countShootingTrajectory(r, g, b);
	}
}

void Snail::decreaseFlashTime() {
	if (flashTime > 0.0f) flashTime -= 0.01f;
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

void Snail::shootBullet(float strength) {
	shooting = true;
	yShooting = 0.0f;
	xShooting = 0.0f;
	angleShooting = bazooka->getAngle() + 10.0f;
	timeShooting = 0.0f;
	speedShooting = log(strength) / log(2) * 6;
	printf("angle: %f ----- speed: %f ---- cosinus: %f, ----- sinus: %f\n", angleShooting, speedShooting, cos(angleShooting * PI / 180), sin(angleShooting * PI / 180));
	bazooka->startShooting();
}

void Snail::countShootingTrajectory(double r, double g, double b) {
	xShooting = speedShooting * timeShooting * cos(angleShooting * PI / 180) * 1.8f;
	yShooting = speedShooting * timeShooting * sin(angleShooting * PI / 180) + 3.0f - 0.5f * 9.806f * pow(timeShooting, 2);
	timeShooting += 0.01f;

	bazooka->moveBullet(xShooting, yShooting, r, g, b);

	// warunek dla uderzajacej kuli
	// to do - roboczo wybuch i znikniecie kuli w punkcie ponizej 0.0
	if (yShooting < 0.0f) {
		shooting = false;
		bazooka->endShooting();
		flashTime = initialFlashTime;
	}
}

bool Snail::getTurn() {
	return turn;
}

void Snail::setTurn(bool t) {
	turn = t;
}

RGBflashLight Snail::getRGB() {
	RGBflashLight rgb;
	//printf("%f\n", flashTime);

	if (flashTime <= 0.0f) {
		rgb.r = 0;
		rgb.g = 0;
		rgb.b = 0;
	}
	else if (flashTime <= initialFlashTime / 2.0) {
		rgb.r = (flashTime/(initialFlashTime / 2.0));
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

AABBObject* Snail::getaabb()
{
    return aabb;
}

Bazooka* Snail::getBazooka() {
	return bazooka;
}

Snail::~Snail()
{
    //dtor
}
