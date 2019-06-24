#include "DrawableElement.h"

DrawableElement::DrawableElement(GLuint t, char *objFileName) {
	M = glm::mat4(1.0f);
	modelObj = new OBJloader();
	modelObj->loadOBJ(objFileName);
	tex = t;
}

void DrawableElement::drawSolid() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, modelObj->get_vertices());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, modelObj->get_normals());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, modelObj->get_texCoords());
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, modelObj->get_colors());

	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVNumber());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void DrawableElement::initTextureDrawing(glm::mat4 P, glm::mat4 V) {
	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::initSolidDrawing(glm::mat4 P, glm::mat4 V) {
	spLambert->use();
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::drawTextured() {

	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, modelObj->get_vertices());

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, modelObj->get_texCoords());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spLambertTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVNumber());

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));
}



void DrawableElement::setBoxes()
{
	int n_vertices = modelObj->getVNumber() * 4;
	float* verts = modelObj->get_vertices();
	float x1 = verts[0], y1 = verts[1], z1 = verts[2]; //min
	float x2 = verts[0], y2 = verts[1], z2 = verts[2]; //max

	for (int i = 4; i < n_vertices; i += 4)
	{
		if (verts[i] < x1)
			x1 = verts[i];
		else if (verts[i] > x2)
			x2 = verts[i];
		if (verts[i + 1] < y1)
			y1 = verts[i + 1];
		else if (verts[i + 1] > y2)
			y2 = verts[i + 1];
		if (verts[i + 2] < z1)
			z1 = verts[i + 2];
		else if (verts[i + 2] > z2)
			z2 = verts[i + 2];
	}

	aabb->setmins(x1, y1, z1);
	aabb->setmaxes(x2, y2, z2);
}


AABBObject* DrawableElement::getaabb()
{
	return aabb;
}