#include "DrawableElement.h"

DrawableElement::DrawableElement(GLuint t, char *objFileName, ShaderProgram *s) {
	M = glm::mat4(1.0f);
	
	aabb = new AABBObject();
	modelObj = new OBJloader();
	modelObj->loadOBJ(objFileName);
	tex = t;
	sp = s;
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
	sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::initSolidDrawing(glm::mat4 P, glm::mat4 V) {
	sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::drawTextured(double rColor, double gColor, double bColor) {
	glUniform4f(sp->u("color"), rColor, gColor, bColor, 1);
	drawCommon();
}

void DrawableElement::drawTextured() {
	glUniform4f(sp->u("color"), 0, 0, 0, 1);
	drawCommon();
}

void DrawableElement::drawCommon() {

	glUniform4f(sp->u("lp"), 0, 10, -6, 0.8); //Wsp�rz�dne �r�d�a �wiat�a zwyk�ego
	glUniform4f(sp->u("lp2"), 0, 0, -5, 1); //Wsp�rz�dne �r�d�a �wiat�a rozb�ysku
	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glEnableVertexAttribArray(sp->a("vertex"));  //W��cz przesy�anie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, modelObj->get_vertices()); //Wska� tablic� z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("normal"));  //W��cz przesy�anie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, modelObj->get_normals()); //Wska� tablic� z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //W��cz przesy�anie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, modelObj->get_texCoords()); //Wska� tablic� z danymi dla atrybutu texCoord0

	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVNumber()); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  //Wy��cz przesy�anie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("normal"));  //Wy��cz przesy�anie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy��cz przesy�anie danych do atrybutu texCoord0
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