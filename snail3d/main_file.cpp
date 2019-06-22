﻿/*
Niniejszy program jest wolnym oprogramowaniem; mo�esz go
rozprowadza� dalej i / lub modyfikowa� na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacj� Wolnego
Oprogramowania - wed�ug wersji 2 tej Licencji lub(wed�ug twojego
wyboru) kt�rej� z p�niejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej�, i� b�dzie on
u�yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domy�lnej
gwarancji PRZYDATNO�CI HANDLOWEJ albo PRZYDATNO�CI DO OKRE�LONYCH
ZASTOSOWA�.W celu uzyskania bli�szych informacji si�gnij do
Powszechnej Licencji Publicznej GNU.

Z pewno�ci� wraz z niniejszym programem otrzyma�e� te� egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
je�li nie - napisz do Free Software Foundation, Inc., 59 Temple
Place, Fifth Floor, Boston, MA  02110 - 1301  USA
*/

#define GLM_FORCE_RADIANS
#define GLM_FORCE_SWIZZLE

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stdlib.h>
#include <stdio.h>
#include "constants.h"
#include "lodepng.h"
#include "shaderprogram.h"
#include "myTeapot.h"
#include "Camera.h"
#include "Snail.h"
#include "AABBObject.h"
#include "StrengthBar.h"
#include "Mountain.h"

float speed_x = 0;
float speed_y = 0;
float speed_up = 0;
float aspectRatio = 1;
float strength = 0;

//ShaderProgram *spLambert;

//Uchwyty na tekstury
GLuint bazookaTex;
GLuint bulletTex;
GLuint snailTex;
GLuint mountainTex;


//Procedura obs�ugi b��d�w
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_A) speed_x = -PI / 2;
		if (key == GLFW_KEY_D) speed_x = PI / 2;
		if (key == GLFW_KEY_W) speed_y = PI / 2;
		if (key == GLFW_KEY_S) speed_y = -PI / 2;
		if (key == GLFW_KEY_UP) speed_up = PI / 2;
		if (key == GLFW_KEY_DOWN) speed_up = -PI / 2;
		if (key == GLFW_KEY_SPACE) strength = 0.1;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_A) speed_x = 0;
		if (key == GLFW_KEY_D) speed_x = 0;
		if (key == GLFW_KEY_W) speed_y = 0;
		if (key == GLFW_KEY_S) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_up = 0;
		if (key == GLFW_KEY_DOWN) speed_up = 0;
		if (key == GLFW_KEY_SPACE) strength = 0;
	}
}

void windowResizeCallback(GLFWwindow* window, int width, int height) {
	if (height == 0) return;
	aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
}



//Funkcja wczytuj�ca tekstur�
GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pami�ci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do kt�rych wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pami�ci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pami�ci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	bazookaTex = readTexture("models/bazooka_tex.jpg");
	bulletTex = readTexture("models/bullet_tex.jpg");
	snailTex = readTexture("models/t0080_0.png");
	mountainTex = readTexture("models/mountain_tex.png");
}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();

	glDeleteTextures(1, &bazookaTex);
	glDeleteTextures(1, &bulletTex);
	glDeleteTextures(1, &snailTex);
	glDeleteTextures(1, &mountainTex);
}




//Procedura rysuj�ca zawarto�� sceny
void drawScene(GLFWwindow* window, Snail* snail, StrengthBar* bar, Mountain* mountain) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	snail->moveSnail(speed_x, speed_y, speed_up);
	snail->draw(speed_up);
	mountain->drawMountain();


	if (strength) {
		bar->draw(strength);
	}
	else {
		strength = 0;
		bar->setLength(0);
	}
	glfwSwapBuffers(window); //Przerzu� tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //Wska�nik na obiekt reprezentuj�cy okno

	glfwSetErrorCallback(error_callback);//Zarejestruj procedur� obs�ugi b��d�w

	if (!glfwInit()) { //Zainicjuj bibliotek� GLFW
		fprintf(stderr, "Nie mo�na zainicjowa� GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utw�rz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Je�eli okna nie uda�o si� utworzy�, to zamknij program
	{
		fprintf(stderr, "Nie mo�na utworzy� okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje si� aktywny i polecenia OpenGL b�d� dotyczy� w�a�nie jego.
	glfwSwapInterval(1); //Czekaj na 1 powr�t plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotek� GLEW
		fprintf(stderr, "Nie mo�na zainicjowa� GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj�ce

	//G��wna p�tla
	float angle_x = 0; //Aktualny k�t obrotu obiektu
	float angle_y = 0; //Aktualny k�t obrotu obiektu
	glfwSetTime(0); //Zeruj timer
	
	Camera* camera = new Camera();
	Mountain* mountain = new Mountain(mountainTex);
	Snail* snail = new Snail(camera, snailTex, bazookaTex, bulletTex);//, spLambert);
	StrengthBar* strenghBar = new StrengthBar(camera);
	
	while (!glfwWindowShouldClose(window)) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{
		//angle_x += speed_x * glfwGetTime(); //Zwi�ksz/zmniejsz k�t obrotu na podstawie pr�dko�ci i czasu jaki up�yna� od poprzedniej klatki
		//angle_y += speed_y * glfwGetTime(); //Zwi�ksz/zmniejsz k�t obrotu na podstawie pr�dko�ci i czasu jaki up�yna� od poprzedniej klatki
		glfwSetTime(0); //Zeruj timer
		drawScene(window, snail, strenghBar, mountain); //Wykonaj procedur� rysuj�c�
		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);
}