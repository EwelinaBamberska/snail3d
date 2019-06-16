#include "Bazooka.h"



Bazooka::Bazooka(Camera* c)
{
	bazookaM = glm::mat4(1.0f);
	camera = c;
}

void Bazooka::drawBazooka(float z, glm::mat4 M) {
	angleOfBazooka += z;
	if (angleOfBazooka > 80.0) angleOfBazooka = 80.0;
	if (angleOfBazooka < -20.0) angleOfBazooka = -20.0;
	float angle1 = angleOfBazooka * 2 * PI / 360;

	spLambert->use();
	glUniform4f(spLambert->u("color"), 1, 1, 0, 1);
	Models::Teapot* teapot = new Models::Teapot();
	bazookaM = glm::translate(M, glm::vec3(0.18f, 0.35f, 0.0f));
	bazookaM = glm::scale(bazookaM, glm::vec3(0.3f, 0.3f, 0.3f));
	bazookaM = glm::rotate(bazookaM, (float)0.5 * PI, glm::vec3(0.0f, -1.0f, 0.0f));
	bazookaM = glm::rotate(bazookaM, angle1, glm::vec3(0.0f, 0.0f, 1.0f));

	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(bazookaM));
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(camera->getP()));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(camera->getV()));

	Models::teapot.drawSolid(); //Draw model
}

Bazooka::~Bazooka()
{
}
