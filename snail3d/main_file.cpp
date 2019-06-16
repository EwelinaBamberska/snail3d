/*
Niniejszy program jest wolnym oprogramowaniem; mo¿esz go
rozprowadzaæ dalej i / lub modyfikowaæ na warunkach Powszechnej
Licencji Publicznej GNU, wydanej przez Fundacjê Wolnego
Oprogramowania - wed³ug wersji 2 tej Licencji lub(wed³ug twojego
wyboru) którejœ z póŸniejszych wersji.

Niniejszy program rozpowszechniany jest z nadziej¹, i¿ bêdzie on
u¿yteczny - jednak BEZ JAKIEJKOLWIEK GWARANCJI, nawet domyœlnej
gwarancji PRZYDATNOŒCI HANDLOWEJ albo PRZYDATNOŒCI DO OKREŒLONYCH
ZASTOSOWAÑ.W celu uzyskania bli¿szych informacji siêgnij do
Powszechnej Licencji Publicznej GNU.

Z pewnoœci¹ wraz z niniejszym programem otrzyma³eœ te¿ egzemplarz
Powszechnej Licencji Publicznej GNU(GNU General Public License);
jeœli nie - napisz do Free Software Foundation, Inc., 59 Temple
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
#include "Landscape.h"

float speed_x = 0;
float speed_y = 0;
float speed_up = 0;
float aspectRatio = 1;
float strength = 0;

//ShaderProgram *spLambert;

//Uchwyty na tekstury
GLuint tex;
GLuint tex1;


//Procedura obs³ugi b³êdów
void error_callback(int error, const char* description) {
	fputs(description, stderr);
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (action == GLFW_PRESS) {
		if (key == GLFW_KEY_A) speed_x = -PI;
		if (key == GLFW_KEY_D) speed_x = PI;
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



//Funkcja wczytuj¹ca teksturê
GLuint readTexture(const char* filename) {
	GLuint tex;
	glActiveTexture(GL_TEXTURE0);

	//Wczytanie do pamiêci komputera
	std::vector<unsigned char> image;   //Alokuj wektor do wczytania obrazka
	unsigned width, height;   //Zmienne do których wczytamy wymiary obrazka
	//Wczytaj obrazek
	unsigned error = lodepng::decode(image, width, height, filename);

	//Import do pamiêci karty graficznej
	glGenTextures(1, &tex); //Zainicjuj jeden uchwyt
	glBindTexture(GL_TEXTURE_2D, tex); //Uaktywnij uchwyt
	//Wczytaj obrazek do pamiêci KG skojarzonej z uchwytem
	glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*)image.data());

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	return tex;
}

//Procedura inicjuj¹ca
/*void initOpenGLProgram(GLFWwindow* window) {
	//initShaders();

	//************Tutaj umieszczaj kod, który nale¿y wykonaæ raz, na pocz¹tku programu************
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);

	spLambert = new ShaderProgram("vertex.glsl", NULL, "fragment.glsl");

	tex0 = readTexture("metal.png");
	tex1 = readTexture("sky.png");
}


//Zwolnienie zasobów zajêtych przez program
void freeOpenGLProgram(GLFWwindow* window) {
	//************Tutaj umieszczaj kod, który nale¿y wykonaæ po zakoñczeniu pêtli g³ównej************
	glDeleteTextures(1, &tex0);
	glDeleteTextures(1, &tex1);
	delete spLambert;
	//freeShaders();
}*/

void initOpenGLProgram(GLFWwindow* window) {
	initShaders();
	//************Place any code here that needs to be executed once, at the program start************
	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);
	glfwSetWindowSizeCallback(window, windowResizeCallback);
	glfwSetKeyCallback(window, keyCallback);
	tex = readTexture("models/t0080_0.png");


}

//Release resources allocated by the program
void freeOpenGLProgram(GLFWwindow* window) {
	freeShaders();
	//glDeleteTextures(1,&tex);

	//************Place any code here that needs to be executed once, after the main loop ends************
}




//Procedura rysuj¹ca zawartoœæ sceny
void drawScene(GLFWwindow* window,  Snail* snail, StrengthBar* bar, Snail* tSnail, Landscape* land) {
	//************Tutaj umieszczaj kod rysuj¹cy obraz******************l
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	/*
	glm::mat4 V = glm::lookAt(
		glm::vec3(0, 0, -5),
		glm::vec3(0, 0, 0),
		glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz widoku

	glm::mat4 P = glm::perspective(50.0f*PI / 180.0f, aspectRatio, 0.01f, 50.0f); //Wylicz macierz rzutowania

	glm::mat4 M = glm::mat4(1.0f);
	M = glm::rotate(M, angle_y, glm::vec3(1.0f, 0.0f, 0.0f)); //Wylicz macierz modelu
	M = glm::rotate(M, angle_x, glm::vec3(0.0f, 1.0f, 0.0f)); //Wylicz macierz modelu

	*/
	//Kostka
	/*float *verts=myCubeVertices;
	float *normals=myCubeNormals;
	float *texCoords=myCubeTexCoords;
	unsigned int vertexCount=myCubeVertexCount;*/

	//Czajnik
	/*float *verts = myTeapotVertices;
	float *normals = myTeapotVertexNormals;
	float *texCoords = myTeapotTexCoords;
	unsigned int vertexCount = myTeapotVertexCount;

	spLambert->use();//Aktywacja programu cieniuj¹cego
	//Przeslij parametry programu cieniuj¹cego do karty graficznej
	glUniformMatrix4fv(spLambert->u("P"), 1, false, glm::value_ptr(P));
	glUniformMatrix4fv(spLambert->u("V"), 1, false, glm::value_ptr(V));
	glUniformMatrix4fv(spLambert->u("M"), 1, false, glm::value_ptr(M));
	glUniform4f(spLambert->u("lp"), 0, 0, -6, 1); //Wspó³rzêdne Ÿród³a œwiat³a

	glUniform1i(spLambert->u("textureMap0"), 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex0);

	glUniform1i(spLambert->u("textureMap1"), 1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, tex1);


	glEnableVertexAttribArray(spLambert->a("vertex"));  //W³¹cz przesy³anie danych do atrybutu vertex
	glVertexAttribPointer(spLambert->a("vertex"), 4, GL_FLOAT, false, 0, verts); //Wska¿ tablicê z danymi dla atrybutu vertex

	glEnableVertexAttribArray(spLambert->a("normal"));  //W³¹cz przesy³anie danych do atrybutu normal
	glVertexAttribPointer(spLambert->a("normal"), 4, GL_FLOAT, false, 0, normals); //Wska¿ tablicê z danymi dla atrybutu normal

	glEnableVertexAttribArray(spLambert->a("texCoord0"));  //W³¹cz przesy³anie danych do atrybutu texCoord0
	glVertexAttribPointer(spLambert->a("texCoord0"), 2, GL_FLOAT, false, 0, texCoords); //Wska¿ tablicê z danymi dla atrybutu texCoord0

	glDrawArrays(GL_TRIANGLES, 0, vertexCount); //Narysuj obiekt

	glDisableVertexAttribArray(spLambert->a("vertex"));  //Wy³¹cz przesy³anie danych do atrybutu vertex
	glDisableVertexAttribArray(spLambert->a("normal"));  //Wy³¹cz przesy³anie danych do atrybutu normal
	glDisableVertexAttribArray(spLambert->a("texCoord0"));  //Wy³¹cz przesy³anie danych do atrybutu texCoord0
	*/
	snail->rotateSnail(speed_x);
	snail->moveSnail(speed_y * 0.001);
	snail->draw();
	snail->drawBazooka(speed_up * 0.02);
	//land->drawSolid();
	//tSnail->draw(speed_up);
	//if (tSnail->getaabb()->check_if_collision(snail->getaabb())) {
	//	printf("TRUE\n");
	//}
	//else
	//	printf("FALSE\n");
	if (strength) {
		bar->draw(strength);
	}
	else {
		strength = 0;
		bar->setLength(0);
	}
	glfwSwapBuffers(window); //Przerzuæ tylny bufor na przedni
}


int main(void)
{
	GLFWwindow* window; //WskaŸnik na obiekt reprezentuj¹cy okno


	glfwSetErrorCallback(error_callback);//Zarejestruj procedurê obs³ugi b³êdów

	if (!glfwInit()) { //Zainicjuj bibliotekê GLFW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLFW.\n");
		exit(EXIT_FAILURE);
	}

	window = glfwCreateWindow(500, 500, "OpenGL", NULL, NULL);  //Utwórz okno 500x500 o tytule "OpenGL" i kontekst OpenGL.

	if (!window) //Je¿eli okna nie uda³o siê utworzyæ, to zamknij program
	{
		fprintf(stderr, "Nie mo¿na utworzyæ okna.\n");
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window); //Od tego momentu kontekst okna staje siê aktywny i polecenia OpenGL bêd¹ dotyczyæ w³aœnie jego.
	glfwSwapInterval(1); //Czekaj na 1 powrót plamki przed pokazaniem ukrytego bufora

	if (glewInit() != GLEW_OK) { //Zainicjuj bibliotekê GLEW
		fprintf(stderr, "Nie mo¿na zainicjowaæ GLEW.\n");
		exit(EXIT_FAILURE);
	}

	initOpenGLProgram(window); //Operacje inicjuj¹ce


	Camera* camera = new Camera();
	Snail* snail = new Snail(camera, tex);//, spLambert);
	Snail* tmpSnail = new Snail(camera, tex);
	StrengthBar* strenghBar = new StrengthBar(camera);
	Landscape* landscape = new Landscape(camera, tex);
	snail->setBoxes();
	tmpSnail->setBoxes();

	//G³ówna pêtla
	float angle_x = 0; //Aktualny k¹t obrotu obiektu
	float angle_y = 0; //Aktualny k¹t obrotu obiektu
	glfwSetTime(0); //Zeruj timer
	while (!glfwWindowShouldClose(window)) //Tak d³ugo jak okno nie powinno zostaæ zamkniête
	{
		//angle_x += speed_x * glfwGetTime(); //Zwiêksz/zmniejsz k¹t obrotu na podstawie prêdkoœci i czasu jaki up³yna³ od poprzedniej klatki
		//angle_y += speed_y * glfwGetTime(); //Zwiêksz/zmniejsz k¹t obrotu na podstawie prêdkoœci i czasu jaki up³yna³ od poprzedniej klatki
		glfwSetTime(0); //Zeruj timer
		drawScene(window, snail, strenghBar, tmpSnail, landscape); //Wykonaj procedurê rysuj¹c¹
		glfwPollEvents(); //Wykonaj procedury callback w zaleznoœci od zdarzeñ jakie zasz³y.
	}

	freeOpenGLProgram(window);

	glfwDestroyWindow(window); //Usuñ kontekst OpenGL i okno
	glfwTerminate(); //Zwolnij zasoby zajête przez GLFW
	exit(EXIT_SUCCESS);
}
