#include "Mountain.h"

Mountain::Mountain(GLuint t, char *objFileName) : DrawableElement(t, objFileName) {
	//M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, -1.5f, 0.0f));
	//modelObj = new OBJloader();
	//mountainObj->loadOBJ("models/ground.obj");
	//tex = t;
}
/*
void Mountain::drawSolid() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, mountainObj->get_vertices());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, mountainObj->get_normals());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, mountainObj->get_texCoords());
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, mountainObj->get_colors());

	glDrawArrays(GL_TRIANGLES, 0, mountainObj->getVNumber());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
} */

void Mountain::drawMountain() {
	// make transformations for bullet

	
	M = glm::scale(M, glm::vec3(1.0f, 1.0f, 1.0f));
	//M = glm::rotate(M, (float)0.5 * PI, glm::vec3(0.0f, 0.0f, 0.0f));

	//glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	//glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));
	drawTextured();
	//drawSolid();
	/*
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, mountainObj->get_vertices());

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, mountainObj->get_texCoords());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spLambertTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, mountainObj->getVNumber());

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord")); */

}