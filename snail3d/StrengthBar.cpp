#include "StrengthBar.h"

StrengthBar::StrengthBar(Camera *c, ShaderProgram* s)
{
	//ctor
	camera = c;
	M = glm::mat4(1.0f);
	maxLength = 100.0f;
	sp = s;
}

void StrengthBar::drawSolid()
{
	/*glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(1);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, myCubeVertices);
	//glVertexAttribPointer(1,4,GL_FLOAT,false,0,snailObj->get_normals());
	//glVertexAttribPointer(2,2,GL_FLOAT,false,0,snailObj->get_texCoords());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, myCubeColors);

	glDrawArrays(GL_TRIANGLES, 0, myCubeVertexCount);

	glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(1);*/
}

void StrengthBar::draw(float s)
{
	if (s)
		length += s;
	if (length > maxLength)	length = 0.0f;
	sp->use();
	glUniform4f(sp->u("color"), 1, 0, 0, 1);

	glm::mat4 newM = glm::translate(M, glm::vec3(0.0f, -1.2f, -1.5f));
	newM = glm::scale(newM, glm::vec3(1.5f * length / 100, 0.1f, 0.1f));
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(camera->getP()));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(camera->getV()));
	glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(newM));
	Models::cube.drawSolid();
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
