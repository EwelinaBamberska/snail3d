#include "Landscape.h"



Landscape::Landscape(Camera* c, GLuint t)
{
	landscapeObj = new OBJloader();
	landscapeObj->loadOBJ("models/Rock_big_single_b_LOD0.obj");
	M = glm::mat4(1.0f);
	M = glm::translate(M, glm::vec3(0.0f, -3.0f, 0.0f));
	M = glm::scale(M, glm::vec3(0.05f, 0.05f, 0.05f));
	camera = c;
	tex = t;
}

void Landscape::drawSolid() {
	spLambert->use();
	glUniform4f(spLambert->u("color"), 0, 1, 0, 1);
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(camera->getP()));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(camera->getV()));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, landscapeObj->get_vertices());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, landscapeObj->get_normals());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, landscapeObj->get_texCoords());
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, landscapeObj->get_colors());

	glDrawArrays(GL_TRIANGLES, 0, landscapeObj->getVNumber());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	/*int vertexCount = landscapeObj->getVNumber();
	float* verts = landscapeObj->get_vertices();
	float* texCoords = landscapeObj->get_texCoords();
	spTextured->use();
	glUniformMatrix4fv(spTextured->u("P"), 1, false, glm::value_ptr(camera->getP()));
	glUniformMatrix4fv(spTextured->u("V"), 1, false, glm::value_ptr(camera->getV()));
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, verts);

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, texCoords);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spLambertTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, vertexCount);

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));*/
}


Landscape::~Landscape()
{
}
