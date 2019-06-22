#include "Bullet.h"

Bullet::Bullet(GLuint t) {
	M = glm::mat4(1.0f);
	bulletObj = new OBJloader();
	bulletObj->loadOBJ("models/bullet.obj");
	tex = t;
}

void Bullet::drawSolid() {
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, bulletObj->get_vertices());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, bulletObj->get_normals());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, bulletObj->get_texCoords());
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, bulletObj->get_colors());

	glDrawArrays(GL_TRIANGLES, 0, bulletObj->getVNumber());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
}

void Bullet::drawBullet(glm::mat4 bazookaM) {
	// make transformations for bullet

	M = glm::translate(bazookaM, glm::vec3(-0.05f, 1.2f, 0.6f));
	M = glm::scale(M, glm::vec3(0.5f, 0.5f, 0.5f));
	//M = glm::rotate(M, (float)0.5 * PI, glm::vec3(0.0f, 0.0f, 0.0f));


	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

	glEnableVertexAttribArray(spTextured->a("vertex"));
	glVertexAttribPointer(spTextured->a("vertex"), 4, GL_FLOAT, false, 0, bulletObj->get_vertices());

	glEnableVertexAttribArray(spTextured->a("texCoord"));
	glVertexAttribPointer(spTextured->a("texCoord"), 2, GL_FLOAT, false, 0, bulletObj->get_texCoords());

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex);
	glUniform1i(spLambertTextured->u("tex"), 0);

	glDrawArrays(GL_TRIANGLES, 0, bulletObj->getVNumber());

	glDisableVertexAttribArray(spTextured->a("vertex"));
	glDisableVertexAttribArray(spTextured->a("texCoord"));


}