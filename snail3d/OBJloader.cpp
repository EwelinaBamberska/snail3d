#include "OBJloader.h"



OBJloader::OBJloader()
{
}


bool OBJloader::loadOBJ(
	const char * path
) {
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_texCoords;
	std::vector< glm::vec3 > temp_normals;

	unsigned int i, j;

	vNumber = 0;

	// open a file
	FILE * file = fopen(path, "r");
	if (file == NULL) {
		printf("Impossible to open the file !\n");
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break;

		if (strcmp(lineHeader, "v") == 0) {
			// add vertices to temp_vertices
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			// add texCoords to temp array
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			temp_texCoords.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			// add normals to temp array
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			// when face - process the vertices and add them to final array
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				printf("File can't be read by our simple parser : ( Try exporting with other options\n");
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

			vNumber += 3;
		}
	}

	final_vertices = new float[vNumber * 4];
	final_texCoords = new float[vNumber * 2];
	final_normals = new float[vNumber * 4];
	final_colors = new float[vNumber * 4];

	j = 0;
	for (i = 0; i < vertexIndices.size(); i++) {
		unsigned int vertexIndex = vertexIndices[i];
		final_vertices[j++] = (temp_vertices[vertexIndex - 1].x);
		final_vertices[j++] = (temp_vertices[vertexIndex - 1].y);
		final_vertices[j++] = (temp_vertices[vertexIndex - 1].z);
		final_vertices[j++] = (1.0f);
	}

	j = 0;
	for (i = 0; i < uvIndices.size(); i++) {
		unsigned int uvIndex = uvIndices[i];
		final_texCoords[j++] = (temp_texCoords[uvIndex - 1].x);
		final_texCoords[j++] = (temp_texCoords[uvIndex - 1].y);
	}

	j = 0;
	for (i = 0; i < normalIndices.size(); i++) {
		unsigned int normalsIndex = normalIndices[i];
		final_normals[j++] = (temp_normals[normalsIndex - 1].x);
		final_normals[j++] = (temp_normals[normalsIndex - 1].y);
		final_normals[j++] = (temp_normals[normalsIndex - 1].z);
		final_normals[j++] = (0.0f);
	}

	j = 0;
	for (i = 0; i < vNumber; i++) {
		final_colors[j++] = (0.7f);
		final_colors[j++] = (1.0f);
		final_colors[j++] = (0.4f);
		final_colors[j++] = (1.0f);
	}

	return true;
}

void OBJloader::write() {
	printf("Vertices: \n");
	for (int i = 0; i < vNumber; i++) {
		std::cout << final_vertices[i] << " ";
		if ((i + 1) % 4 == 0) std::cout << std::endl;
	}

	printf("Tex coords: \n");
	for (int i = 0; i < vNumber; i++) {
		std::cout << final_texCoords[i] << " ";
		if ((i + 1) % 2 == 0) std::cout << std::endl;
	}

	printf("Normals: \n");
	for (int i = 0; i < vNumber; i++) {
		std::cout << final_normals[i] << " ";
		if ((i + 1) % 4 == 0) std::cout << std::endl;
	}

	printf("Colors: \n");
	for (int i = 0; i < vNumber; i++) {
		std::cout << final_colors[i] << " ";
		if ((i + 1) % 4 == 0) std::cout << std::endl;
	}
}

float* OBJloader::get_vertices() {
	return final_vertices;
}

float* OBJloader::get_normals() {
	return final_normals;
}

float* OBJloader::get_texCoords() {
	return final_texCoords;
}

float* OBJloader::get_colors() {
	return final_colors;
}

int OBJloader::getVNumber() {
	return vNumber;
}

OBJloader::~OBJloader()
{
}
