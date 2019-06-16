#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <fstream>
#include <iostream>
#include <string>

class OBJloader
{
public:
	OBJloader();
	virtual ~OBJloader();
	bool loadOBJ(
		const char * path
	);
	void write();
	int getVNumber();
	float* get_vertices();
	float* get_texCoords();
	float* get_normals();
	float* get_colors();
protected:
private:

	float* final_vertices;
	float* final_texCoords;
	float* final_normals;
	float* final_colors;

	int vNumber;
};

#endif // OBJLOADER_H
