#include "DrawableElement.h"

DrawableElement::DrawableElement(GLuint t, char *objFileName, ShaderProgram *s) {
	M = glm::mat4(1.0f);

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
	/*sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));*/
	sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::initSolidDrawing(glm::mat4 P, glm::mat4 V) {
	sp->use();
	glUniformMatrix4fv(sp->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(sp->u("V"), 1, false, glm::value_ptr(V));
}

void DrawableElement::drawTextured() {
	/*
	glEnableVertexAttribArray(sp->a("vertex"));
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, modelObj->get_vertices());

	glEnableVertexAttribArray(sp->a("texCoord"));
	glVertexAttribPointer(sp->a("texCoord"), 2, GL_FLOAT, false, 0, modelObj->get_texCoords());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(sp->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVNumber());

	glDisableVertexAttribArray(sp->a("vertex"));
	glDisableVertexAttribArray(sp->a("texCoord"));*/

	//sp->use();//Aktywacja programu cieniuj¹cego
	//Przeslij parametry programu cieniuj¹cego do karty graficznej
	//glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
	glUniform4f(sp->u("lp"), 0, 0, -6, 1); //Wspó³rzêdne Ÿród³a œwiat³a

	glUniform1i(sp->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);

	glUniform1i(sp->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex);


	glEnableVertexAttribArray(sp->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(sp->a("vertex"), 4, GL_FLOAT, false, 0, modelObj->get_vertices()); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(sp->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
	glVertexAttribPointer(sp->a("normal"), 4, GL_FLOAT, false, 0, modelObj->get_normals()); //Wska¿ tablicê z danymi dla atrybutu normal

	glEnableVertexAttribArray(sp->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord0
	glVertexAttribPointer(sp->a("texCoord0"), 2, GL_FLOAT, false, 0, modelObj->get_texCoords()); //Wska¿ tablicê z danymi dla atrybutu texCoord0

	glDrawArrays(GL_TRIANGLES, 0, modelObj->getVNumber()); //Narysuj obiekt

	glDisableVertexAttribArray(sp->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(sp->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
	glDisableVertexAttribArray(sp->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0

}