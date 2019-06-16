#include "Snail.h"



Snail::Snail(Camera* c, GLuint t)// , ShaderProgram* s)
{
	//spLambert = s;
    M = glm::mat4(1.0f);
    camera = c;
    snailObj = new OBJloader();
    snailObj->loadOBJ("models/snail.obj");
    aabb = new AABBObject();
	tex = t;
	bazooka = new Bazooka(camera);
}


void Snail::moveSnail(float y)
{
    M = glm::translate(M, glm::vec3(0.0f, 0.0f, 1.0f * y)); //Compute model matrix
	//aabb->setz(aabb->getmins()[2] + 1.0f * y, aabb->getmaxes()[2] + 1.0f * y);
	
	float oldmin = sqrt(pow(aabb->getmins()[1], 2) - pow(aabb->getmins()[2], 2));
	float oldmax = sqrt(pow(aabb->getmaxes()[1], 2) - pow(aabb->getmaxes()[2], 2));
    aabb->setz(aabb->getmins()[2] + cos(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[2] + cos(angleOfSnail * PI / 180) * (y));
	aabb->sety(aabb->getmins()[1] + sin(angleOfSnail * PI / 180) * (y), aabb->getmaxes()[1] + sin(angleOfSnail * PI / 180) * (y));
}

void Snail::rotateSnail(float x)
{
	angleOfSnail += x / ( 2.0 * PI * 6.25);
	if (angleOfSnail > 360)	angleOfSnail -= 360;
	else if (angleOfSnail < -360)	angleOfSnail += 360;
	x = x / (2.0 * PI * 360.0);
    M = glm::rotate(M, x, glm::vec3(0.0f, -1.0f, 0.0f));
}

void Snail::drawSolid()
{
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);


    glVertexAttribPointer(0,4,GL_FLOAT,false,0,snailObj->get_vertices());
    glVertexAttribPointer(1,4,GL_FLOAT,false,0,snailObj->get_normals());
    glVertexAttribPointer(2,2,GL_FLOAT,false,0,snailObj->get_texCoords());
    glVertexAttribPointer(3,4,GL_FLOAT,false,0,snailObj->get_colors());

    glDrawArrays(GL_TRIANGLES,0,snailObj->getVNumber());

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
}

void Snail::drawBazooka(float z){
	bazooka->drawBazooka(z, M);
}

void Snail::draw()
{
	/*z = 0.05 * z;
    spLambert->use();
    glUniform4f(spLambert->u("color"),0,1,0,1);
    glUniformMatrix4fv(spLambert->u("P"),1,false,glm::value_ptr(camera->getP()));
    glUniformMatrix4fv(spLambert->u("V"),1,false,glm::value_ptr(camera->getV()));
    glUniformMatrix4fv(spLambert->u("M"),1,false,glm::value_ptr(M));
    drawSolid();*/
    //drawBazooka(z);


    int vertexCount = snailObj->getVNumber();
    float* verts = snailObj->get_vertices();
    float* texCoords = snailObj->get_texCoords();
    spTextured->use();
    glUniformMatrix4fv(spTextured->u("P"),1,false,glm::value_ptr(camera->getP()));
    glUniformMatrix4fv(spTextured->u("V"),1,false,glm::value_ptr(camera->getV()));
    glUniformMatrix4fv(spTextured->u("M"),1,false,glm::value_ptr(M));

    glEnableVertexAttribArray(spTextured->a("vertex"));
    glVertexAttribPointer(spTextured->a("vertex"),4,GL_FLOAT,false,0,verts);

    glEnableVertexAttribArray(spTextured->a("texCoord"));
    glVertexAttribPointer(spTextured->a("texCoord"),2,GL_FLOAT,false,0,texCoords);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,tex);
    glUniform1i(spLambertTextured->u("tex"),0);

    glDrawArrays( GL_TRIANGLES, 0, vertexCount );

    glDisableVertexAttribArray(spTextured->a("vertex"));
    glDisableVertexAttribArray(spTextured->a("texCoord"));
	
}

void Snail::setBoxes()
{
    int n_vertices = snailObj->getVNumber() * 4;
    float* verts = snailObj->get_vertices();
    float x1 = verts[0], y1 = verts[1], z1 = verts[2]; //min
    float x2 = verts[0], y2 = verts[1], z2 = verts[2]; //max

    for(int i = 4; i < n_vertices; i+=4)
    {
        if(verts[i] < x1)
            x1 = verts[i];
        else if(verts[i] > x2)
            x2 = verts[i];
        if(verts[i+1] < y1)
            y1 = verts[i+1];
        else if(verts[i+1] > y2)
            y2 = verts[i+1];
        if(verts[i+2] < z1)
            z1 = verts[i+2];
        else if(verts[i+2] > z2)
            z2 = verts[i+2];
    }

    aabb->setmins(x1, y1, z1);
    aabb->setmaxes(x2, y2, z2);
}

AABBObject* Snail::getaabb()
{
    return aabb;
}

glm::mat4 Snail::getM() {
	return M;
}

Bazooka* Snail::getBazooka() {
	return bazooka;
}



Snail::~Snail()
{
    //dtor
}
