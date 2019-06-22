/*
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "sphere.h"


namespace Models {
	
	Sphere sphere;

	Sphere::Sphere() {
		buildSphere(1,12,12);
	}
	
	Sphere::Sphere(float r,float divs1,float divs2) {
		buildSphere(r,divs1,divs2);
	}
	
	Sphere::~Sphere() {		
	}
	
	inline float Sphere::d2r(float deg) {
		return PI*deg/180.0f;
	}

	vec4 Sphere::generateSpherePoint(float r,float alpha,float beta) {
		alpha=d2r(alpha);
		beta=d2r(beta);
		return vec4(r*cos(alpha)*cos(beta),r*cos(alpha)*sin(beta),r*sin(alpha),1.0f);
	}

	vec4 Sphere::computeVertexNormal(float alpha,float beta) {
		alpha=d2r(alpha);
		beta=d2r(beta);
		return vec4(cos(alpha)*cos(beta),cos(alpha)*sin(beta),sin(alpha),0.0f);
	}

	vec4 Sphere::computeFaceNormal(vector<vec4> &face) {
		vec3 a=vec3(face[1]-face[0]);
		vec3 b=vec3(face[2]-face[0]);
		
		return normalize(vec4(cross(b,a),0.0f));
	}

	void Sphere::generateSphereFace(vector<vec4> &vertices, vector<vec4> &vertexNormals, vec4 &faceNormal,float r,float alpha,float beta,float step_alpha,float step_beta) {
		vertices.clear();
		vertexNormals.clear();	
		
		vertices.push_back(generateSpherePoint(r,alpha,beta));
		vertices.push_back(generateSpherePoint(r,alpha+step_alpha,beta));
		vertices.push_back(generateSpherePoint(r,alpha+step_alpha,beta+step_beta));
		vertices.push_back(generateSpherePoint(r,alpha,beta+step_beta));
		
		faceNormal=computeFaceNormal(vertices);
		
		vertexNormals.push_back(computeVertexNormal(alpha,beta));
		vertexNormals.push_back(computeVertexNormal(alpha+step_alpha,beta));
		vertexNormals.push_back(computeVertexNormal(alpha+step_alpha,beta+step_beta));
		vertexNormals.push_back(computeVertexNormal(alpha,beta+step_beta));
	}



	void Sphere::buildSphere(float r,float mainDivs,float tubeDivs) {
		vector<vec4> face;
		vector<vec4> faceVertexNormals;
		vec4 normal;

		internalVertices.clear();
		internalFaceNormals.clear();
		internalVertexNormals.clear();
			
		float mult_alpha=180.0f/tubeDivs;
		float mult_beta=360.0f/mainDivs;
		
		for (int alpha=0;alpha<round(tubeDivs);alpha++) {			
			for (int beta=0;beta<round(mainDivs);beta++) {
				
				generateSphereFace(face,faceVertexNormals,normal,r,alpha*mult_alpha-90.0f,beta*mult_beta,mult_alpha, mult_beta);			
				
				internalVertices.push_back(face[0]);
				internalVertices.push_back(face[1]);
				internalVertices.push_back(face[2]);
				
				internalVertices.push_back(face[0]);
				internalVertices.push_back(face[2]);
				internalVertices.push_back(face[3]);
				
				internalVertexNormals.push_back(faceVertexNormals[0]);
				internalVertexNormals.push_back(faceVertexNormals[1]);
				internalVertexNormals.push_back(faceVertexNormals[2]);
				
				internalVertexNormals.push_back(faceVertexNormals[0]);
				internalVertexNormals.push_back(faceVertexNormals[2]);
				internalVertexNormals.push_back(faceVertexNormals[3]);
							
				for (int i=0;i<6;i++) internalFaceNormals.push_back(normal);
				
				
			}
		}
		
		vertices=(float*)internalVertices.data();
		normals=(float*)internalFaceNormals.data();
		vertexNormals=(float*)internalVertexNormals.data();
		internalTexCoords.clear();

		for (int i=0;i<internalVertexNormals.size();i++) {
            internalTexCoords.push_back(vec2(internalVertexNormals[i].x,internalVertexNormals[i].y));
		    internalColors.push_back(vec4(1.0f,1.0f,0.0f,1.0f));
		}
        colors=(float*)internalColors.data();
		texCoords=(float*)internalTexCoords.data();
		vertexCount=internalVertices.size();
	}

	void Sphere::drawSolid(bool smooth) {

		glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);


        glVertexAttribPointer(0,4,GL_FLOAT,false,0,vertices);
        if (!smooth) glVertexAttribPointer(1,4,GL_FLOAT,false,0,normals);
        else glVertexAttribPointer(1,4,GL_FLOAT,false,0,vertexNormals);
        glVertexAttribPointer(2,2,GL_FLOAT,false,0,texCoords);
        glVertexAttribPointer(3,4,GL_FLOAT,false,0,colors);

        glDrawArrays(GL_TRIANGLES,0,vertexCount);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);

	}


}
