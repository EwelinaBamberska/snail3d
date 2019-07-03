#ifndef STRENGTHBAR_H
#define STRENGTHBAR_H

#include "DrawableElement.h"


class StrengthBar : public DrawableElement
{
public:
	StrengthBar(GLuint t, char*fileName, ShaderProgram* sp);
	virtual ~StrengthBar();
	void loadCube();
	void drawSolid();
	void draw(float s);
	void setLength(float l);
	float getLength();
	float getMaxLength();

protected:

private:
	glm::mat4 M;
	float length;
	float maxLength;
};

#endif // STRENGTHBAR_H
