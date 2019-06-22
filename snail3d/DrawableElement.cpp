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

void DrawableElement::initDrawing(glm::mat4 P, glm::mat4 V) {
	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::drawTextured() {
	//glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

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