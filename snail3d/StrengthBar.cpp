#include "StrengthBar.h"


StrengthBar::StrengthBar(GLuint tex, char* fileName, ShaderProgram* s) : DrawableElement (tex, fileName, s)
{
	//ctor
	/*camera = c;
	M = glm::mat4(1.0f);
	
	sp = s;*/
	M = glm::mat4(1.0f);
	maxLength = 100.0f;
	length = 0.0f;
}

void StrengthBar::drawSolid()
{
}

void StrengthBar::draw(float s)
{
	if(s)
	length += s;
	if (length > maxLength)	length = 0.0f;

	glm::mat4 newM = glm::translate(M, glm::vec3(0.0f, 3.0f, -5.0f));
	newM = glm::scale(newM, glm::vec3(1.5f * length / 100.0f, 0.2f, 0.2f));

	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(newM));
	drawTextured();
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
