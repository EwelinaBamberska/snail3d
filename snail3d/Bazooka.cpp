#include "Bazooka.h"

Bazooka::Bazooka(GLuint bazookaT, GLuint bulletT) {
	angle = 0.0f;
	bazookaObj = new OBJloader();
	bazookaObj->loadOBJ("models/bazooka.obj");
	M = glm::mat4(1.0f);
	bullet = new Bullet(bulletT);
	tex = bazookaT;
}

void Bazooka::drawSolid() { 
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);


	glVertexAttribPointer(0, 4, GL_FLOAT, false, 0, bazookaObj->get_vertices());
	glVertexAttribPointer(1, 4, GL_FLOAT, false, 0, bazookaObj->get_normals());
	glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, bazookaObj->get_texCoords());
	glVertexAttribPointer(3, 4, GL_FLOAT, false, 0, bazookaObj->get_colors());

	glDrawArrays(GL_TRIANGLES, 0, bazookaObj->getVNumber());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);

	
}

void Bazooka::drawBazooka(float z, glm::mat4 snailM) {
	angle += z;
	if(angle > 80.0) angle = 80.0;
	if(angle < -20.0) angle = -20.0;
	float angle_conversed = angle * 2 * PI/ 360;
	
	M = glm::translate(snailM, glm::vec3(0.3f, 0.3f, 0.0f));
	M = glm::scale(M, glm::vec3(0.2f, 0.2f, 0.2f));
	M = glm::rotate(M, (float)0.5 * PI, glm::vec3(1.0f, 0.0f, 0.0f));
	M = glm::rotate(M, angle_conversed, glm::vec3(-1.0f, 0.0f, 0.0f));

	//glUniform4f(spLambert->u("color"), 1, 1, 0, 1);
	glUniformMatrix4fv(spTextured->u("M"), 1, false, glm::value_ptr(M));

	//drawSolid(); //draw model

	// draw bullet
	//bullet->drawBullet(M);

	glEnableVertexAttribArray(spTextured->a("vertex"));
    glVertexAttribPointer(spTextured->a("vertex"),4,GL_FLOAT,false,0, bazookaObj->get_vertices());

    glEnableVertexAttribArray(spTextured->a("texCoord"));
    glVertexAttribPointer(spTextured->a("texCoord"),2,GL_FLOAT,false,0, bazookaObj->get_texCoords());

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glUniform1i(spLambertTextured->u("tex"),0);

    glDrawArrays( GL_TRIANGLES, 0, bazookaObj->getVNumber());

    glDisableVertexAttribArray(spTextured->a("vertex"));
    glDisableVertexAttribArray(spTextured->a("texCoord"));

	bullet->drawBullet(M);
}