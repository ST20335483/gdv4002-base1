#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include "Emitter.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "blackHole.h"
#include "glPrint.h"
#include <bitset>
#include <random>

std::bitset<5> keys{ 0x0 };

using namespace std;

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);
void deleteAsteroids(GLFWwindow* window, double tDelta);
void asteroidHit(GLFWwindow*, double tDelta);

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 10.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthFunc(GL_ALWAYS);

	GLuint playerTexture = loadTexture("Resources\\Textures\\player1_ship.png");
	Player* mainPlayer = new Player(glm::vec2(-2.5f, 0.0f), 0.0f, glm::vec2(0.25f, 0.25f), playerTexture, 2.0f, 2.0f);
	addObject("player", mainPlayer);

	GLuint centerTexture = loadTexture("Resources\\Textures\\black_hole.png");
	BlackHole* centerHole = new BlackHole(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), centerTexture);
	addObject("blackHole", centerHole);

	Emitter* emitter1 = new Emitter(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.0f, 0.0f), 0.05f);
	addObject("emitter", emitter1);

	setKeyboardHandler(myKeyboardHandler);

	setUpdateFunction(deleteAsteroids, false);

	//setRenderFunction(textRender);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

//map keys
void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, true);
			break;

		case GLFW_KEY_W:
			keys[Key::W] = true;
			break;

		case GLFW_KEY_S:
			keys[Key::S] = true;
			break;

		case GLFW_KEY_A:
			keys[Key::A] = true;
			break;

		case GLFW_KEY_D:
			keys[Key::D] = true;
			break;

		case GLFW_KEY_SPACE:
			keys[Key::SPACE] = true;
			break;
		}
	}
	else if (action == GLFW_RELEASE)
	{
		switch (key)
		{
		case GLFW_KEY_W:
			keys[Key::W] = false;
			break;

		case GLFW_KEY_S:
			keys[Key::S] = false;
			break;

		case GLFW_KEY_A:
			keys[Key::A] = false;
			break;

		case GLFW_KEY_D:
			keys[Key::D] = false;
			break;

		case GLFW_KEY_SPACE:
			keys[Key::SPACE] = false;
			break;
		}
	}
}

void deleteAsteroids(GLFWwindow* window, double tDelta)
{

	asteroidHit(window, tDelta);

	GameObjectCollection asteroids = getObjectCollection("Asteroid");

	for (int i = 0; i < asteroids.objectCount; i++)
	{
		if (asteroids.objectArray[i]->position.y < -(getViewplaneHeight() / 2.0f))
		{
			deleteObject(asteroids.objectArray[i]);
		}
		else if (asteroids.objectArray[i]->position.y > (getViewplaneHeight() / 2.0f))
		{
			deleteObject(asteroids.objectArray[i]);
		}
		else if (asteroids.objectArray[i]->position.x < -(getViewplaneWidth() / 2.0f))
		{
			deleteObject(asteroids.objectArray[i]);
		}
		else if (asteroids.objectArray[i]->position.x > (getViewplaneWidth() / 2.0f))
		{
			deleteObject(asteroids.objectArray[i]);
		}
	}
}

void asteroidHit(GLFWwindow* window, double tDelta)
{
	GameObjectCollection asteroids = getObjectCollection("Asteroid");
	GameObjectCollection bullets = getObjectCollection("Bullet");

	for (int asteroidMarker = 0; asteroidMarker < asteroids.objectCount; asteroidMarker++)
	{
		for (int bulletMarker = 0; bulletMarker < bullets.objectCount; bulletMarker++)
		{
			GameObject2D* bullet = bullets.objectArray[bulletMarker];
			GameObject2D* asteroid = asteroids.objectArray[asteroidMarker];

			glm::vec2 distVector = bullet->position - asteroid->position;

			float distance = sqrt(pow(distVector.x, 2) + pow(distVector.y, 2));

			float sumRadius = (bullet->size.x / 2) + (asteroid->size.x / 2);

			if (distance < sumRadius)
			{
				deleteObject(bullets.objectArray[bulletMarker]);
				deleteObject(asteroids.objectArray[asteroidMarker]);
			}
		}
	}
}