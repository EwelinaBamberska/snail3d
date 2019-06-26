/*
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
#include <vector>

int speed_x = 0;
float speed_y = 0;
float speed_up = 0;
float aspectRatio = 1;
float strength = 0;
bool changeActiveSnail = false;
int numberOfSnails = 5;
bool strengthReleased = false;
bool shooting = false;

//ShaderProgram *spLambert;
ShaderProgram* sp;


//Uchwyty na tekstury
GLuint bazookaTex;
GLuint bulletTex;
GLuint snailTex;
GLuint mountainTex;
GLuint blueTex;
GLuint redTex;


//Procedura obs�ugi b��d�w
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		//if (key == GLFW_KEY_A) speed_x = -PI;
		//if (key == GLFW_KEY_D) speed_x = PI;
		if (key == GLFW_KEY_W) speed_y = PI / 2;
		if (key == GLFW_KEY_S) speed_y = -PI / 2;
		if (key == GLFW_KEY_UP) speed_up = PI / 2;
		if (key == GLFW_KEY_DOWN) speed_up = -PI / 2;
		if ( key == GLFW_KEY_SPACE) strength = 0.1;
	}
	if (action == GLFW_RELEASE) {
		if (key == GLFW_KEY_A) speed_x = 1;
		if (key == GLFW_KEY_D) speed_x = -1;
		if (key == GLFW_KEY_W) speed_y = 0;
		if (key == GLFW_KEY_S) speed_y = 0;
		if (key == GLFW_KEY_UP) speed_up = 0;
		if (key == GLFW_KEY_DOWN) speed_up = 0;
		if ( key == GLFW_KEY_SPACE) {
			strength = 0;
			strengthReleased = true;
		}		
		if (key == GLFW_KEY_TAB) changeActiveSnail = true;
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
	//initShaders();
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	snailTex = readTexture("models/t0080_0.png");
	mountainTex = readTexture("models/mountain_tex.png");
	bazookaTex = readTexture("models/bazooka_tex.png");
	bulletTex = readTexture("models/bullet_tex.png");
	blueTex = readTexture("models/blue_texture.png");
	redTex = readTexture("models/red_texture.png");
	sp = new ShaderProgram("vertex.glsl", NULL, "fragment.glsl");

}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	//freeShaders();

	glDeleteTextures(1, &bazookaTex);
	glDeleteTextures(1, &bulletTex);
	glDeleteTextures(1, &snailTex);
	glDeleteTextures(1, &mountainTex);
	glDeleteTextures(1, &blueTex);
	glDeleteTextures(1, &redTex);
	delete sp;

}

int getActiveSnailIndex(std::vector<Snail*> snails) {
	for (int i = 0; i < snails.size(); i++) {
		if (snails[i]->getTurn() == true) {
			return i;
		}
	}
}

//Procedura rysuj�ca zawarto�� sceny
void drawScene(GLFWwindow* window, StrengthBar* bar, Mountain* mountain, std::vector<Snail*> snails) { //  Snail* snail) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	RGBflashLight rgb;

	for (int i = 0; i < snails.size(); i++) {
		rgb = snails[i]->getRGB();
		if (rgb.r > 0) {
			break;
		}
	}

	// narysuj gure
	mountain->drawMountain(rgb.r, rgb.g, rgb.b);

	int active = getActiveSnailIndex(snails);

	// na przycisk "TAB" zmien aktywnego slimaka
	if (changeActiveSnail == true) {
		changeActiveSnail = false;

		snails[active]->setTurn(false);
		snails[(active + 1) % 5]->setTurn(true);
		active = (active + 1) % 5;
	}

	// narysuj slimaki
	for (int i = 0; i < snails.size(); i++) {
		if (snails[i]->getIfLive()) {
			if (snails[i]->getTurn() == true) {
				snails[i]->rotateSnail(speed_x);
				speed_x = 0;
				
				snails[i]->moveSnail(speed_y * 0.005);
				//if (speed_y) {
				//	//obliczanie y
				float translateY1 = mountain->getYPosition(snails[i]->getaabb()->getmaxes()[0], snails[i]->getaabb()->getmaxes()[2], snails[i]->getAngle(), snails[i]->getLasty());
				float translateY2 = mountain->getYPosition(snails[i]->getaabb()->getmins()[0], snails[i]->getaabb()->getmins()[2], snails[i]->getAngle(), snails[i]->getLasty());
				//printf("%f %f\n", translateY1, translateY2);
				//snails[i]->setYPos((translateY1 + translateY2) / 2);
				float max = translateY1 > translateY2 ? translateY1 : translateY2;
				snails[i]->getaabb()->sety(max);
				snails[i]->getBazooka()->getBullet()->getaabb()->setyforBullet(snails[i]->getLasty() - max);			
				snails[i]->setLastY(max);

				//}
				if (snails[i]->getShooting()) {
					for (int j = 0; j < snails.size(); j++) {
						//printf("%d X min %f max %f, \t Z min %f max %f\n",j, snails[i]->getaabb()->getmins()[0], snails[i]->getaabb()->getmaxes()[0], snails[i]->getaabb()->getmins()[2], snails[i]->getaabb()->getmaxes()[2]);
						//printf("SPRAWDZA\n");
						if (i != j && snails[j]->getIfLive() && snails[i]->getBazooka()->getBullet()->getaabb()->check_if_collision(snails[j]->getaabb())) {
							snails[j]->loseLife();
							//printf("%d X min %f max %f, \t Z min %f max %f\n", j, snails[j]->getaabb()->getmins()[0], snails[j]->getaabb()->getmaxes()[0], snails[j]->getaabb()->getmins()[2], snails[j]->getaabb()->getmaxes()[2]);
							//printf("bullet %d X min %f max %f, \t Z min %f max %f\n", j, snails[j]->getBazooka()->getBullet()->getaabb()->getmins()[0], snails[j]->getBazooka()->getBullet()->getaabb()->getmaxes()[0], snails[j]->getBazooka()->getBullet()->getaabb()->getmins()[2], snails[j]->getaabb()->getmaxes()[2]);
							//snails[i]->getBazooka()->getBullet()->setExplosion();
							printf("%d\n", snails[i]->getBazooka()->getBullet()->getExplosion());
							printf("KOLIZJA Z %d\n", j);
							snails[i]->setShooting();
							shooting = false;
							//changeActiveSnail = true;
							break;
						}
					}
				}

			}
			snails[i]->draw(speed_up, rgb.r, rgb.g, rgb.b);
			if (shooting) {
				if (snails[i]->getTimeShooting() > 10.0f) {
					snails[i]->setShooting();
					//changeActiveSnail = true;
					shooting = false;
				}
			}
		}
	}

	// narysuj pasek sily
	if (strength) {
		bar->draw(strength);
	}
	else {
		if (strengthReleased) {
			strengthReleased = false;
			shooting = true;
			snails[active]->shootBullet(bar->getLength());
		}
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
	glfwSetTime(0); //Zeruj timer

	Camera* camera = new Camera();


	char mountainName[] = "models/mountain.obj";
	char snailName[] = "models/snail.obj";

	int i = 0;
	std::vector<Snail*> snails;


	Mountain* mountain = new Mountain(mountainTex, mountainName, sp);

	for (i = 0; i < numberOfSnails; i++) {
		snails.push_back(new Snail(camera, snailName, snailTex, bazookaTex, bulletTex, false, sp, blueTex, redTex));
		snails[snails.size() - 1]->setBoxes();

		snails[snails.size() - 1]->setRandomCoords(i);

		float translateY1 = mountain->getYPosition(snails[i]->getaabb()->getmaxes()[0], snails[i]->getaabb()->getmaxes()[2], snails[i]->getAngle(), snails[i]->getLasty());
		float translateY2 = mountain->getYPosition(snails[i]->getaabb()->getmins()[0], snails[i]->getaabb()->getmins()[2], snails[i]->getAngle(), snails[i]->getLasty());
		//snails[i]->setYPos((translateY1 + translateY2) / 2);
		snails[i]->getaabb()->sety((translateY1 + translateY2) / 2);
		snails[i]->setLastY((translateY1 + translateY2) / 2);
	}

	snails[0]->setTurn(true);
	//Snail* snail = new Snail(camera, snailName, snailTex, bazookaTex, bulletTex, true);//, spLambert);
	StrengthBar* strenghBar = new StrengthBar(camera, sp);

	while (!glfwWindowShouldClose(window)) //Tak d�ugo jak okno nie powinno zosta� zamkni�te
	{

		glfwSetTime(0); //Zeruj timer
		drawScene(window, strenghBar, mountain, snails); // ,snail)		//Wykonaj procedur� rysuj�c�
		glfwPollEvents(); //Wykonaj procedury callback w zalezno�ci od zdarze� jakie zasz�y.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usu� kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zaj�te przez GLFW
	exit(EXIT_SUCCESS);
}