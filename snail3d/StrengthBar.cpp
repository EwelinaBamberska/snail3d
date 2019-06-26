#include "StrengthBar.h"

StrengthBar::StrengthBar(Camera *c, ShaderProgram* s, GLuint tex, char * objFileName) : DrawableElement(tex, objFileName, s)
{
	camera = c;
	maxLength = 100.0f;
	length = 0.0f;

	M = glm::translate(M, glm::vec3(0.0f, 7.0f, -5.0f)); 
	M = glm::scale(M, glm::vec3(1.5f * length / 100, 0.1f, 1.5f));
	M = rotate(M, PI / 2, glm::vec3(1.0f, 0.0f, 0.0f));
}

void StrengthBar::draw(float s)
{
	if(s)
		length += s;

	if (length > maxLength)	length = 0.0f;
		sp->use();


	//glm::mat4 newM = glm::translate(M, glm::vec3(0.0f, 7.0f, -5.0f));
	
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));

	drawTextured();

	/*glUniform4f(sp->u("color"), 1, 0, 0, 1);

	glm::mat4 newM = glm::translate(M, glm::vec3(0.0f, -1.2f, -1.5f));
	newM = glm::scale(newM, glm::vec3(1.5f * length / 100, 0.1f, 0.1f));
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(camera->getP()));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(camera->getV()));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(newM));
	Models::cube.drawSolid();*/
}

void StrengthBar::setLength(float l) {
	length = 0;
}

void StrengthBar::loadCube() {

}

float StrengthBar::getLength() {
	return length;
}

float StrengthBar::getMaxLength() {
	return maxLength;
}

StrengthBar::~StrengthBar()
{
	//dtor
}
