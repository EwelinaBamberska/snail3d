#pragma once
#include "DrawableElement.h"
class HealthBar : public DrawableElement
{
public:
	HealthBar(GLuint tex, char* name, ShaderProgram* sp);
	~HealthBar();
	void drawHealthBar(glm::mat4 M, float y);
	void setLength();
	float getLength();
private:
	float length;
};

