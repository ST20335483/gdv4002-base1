#include "Engine.h"
#include "Keys.h"
#include "Player.h"
#include "Enemy.h"
#include "Missile.h"
#include "Emitter.h"
#include <bitset>
#include <random>

std::bitset<5> keys{ 0x0 };

using namespace std;

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

void deleteSnowflakes(GLFWwindow* window, double tDelta);

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
	Player* mainPlayer = new Player(glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), playerTexture, 2.0f, 2.0f);
	addObject("player", mainPlayer);

	// 1. Load enemy texture 
	GLuint enemyTexture = loadTexture("Resources\\Textures\\asteroid.png");

	// 2. Create enemy objects

	//Enemy* enemy1 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), enemyTexture, 0.0f, glm::radians(45.0f), rand() % 361);
	//Enemy* enemy2 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), enemyTexture, 0.0f, glm::radians(90.0f), rand() % 361);
	//Enemy* enemy3 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), enemyTexture, 0.0f, glm::radians(60.0f), rand() % 361);
	//Enemy* enemy4 = new Enemy(glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(1.0f, 1.0f), enemyTexture, 0.0f, glm::radians(30.0f), rand() % 361);

	Emitter* emitter1 = new Emitter(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), 0.05f);
	//Emitter* emitter2 = new Emitter(glm::vec2(0.0f, -(getViewplaneHeight() / 2.0f * 1.2f)), glm::vec2(getViewplaneWidth() / 2.0f, 0.0f), 0.05f);
	//Emitter* emitter3 = new Emitter(glm::vec2((getViewplaneWidth() / 2.0f * 1.2f), 0.0f), glm::vec2(getViewplaneHeight() / 2.0f, 0.0f), 0.05f);
	//Emitter* emitter4 = new Emitter(glm::vec2(-(getViewplaneWidth() / 2.0f * 1.2f), 0.0f), glm::vec2(getViewplaneHeight() / 2.0f, 0.0f), 0.05f);

	// Add enemy objects to the engine
	//addObject("enemy1", enemy1);
	//addObject("enemy2", enemy2);
	//addObject("enemy3", enemy3);
	//addObject("enemy4", enemy4);

	addObject("emitter", emitter1);
	//addObject("emitter", emitter2);
	//addObject("emitter", emitter3);
	//addObject("emitter", emitter4);

	setKeyboardHandler(myKeyboardHandler);

	setUpdateFunction(deleteSnowflakes, false);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

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

void deleteSnowflakes(GLFWwindow* window, double tDelta)
{
	GameObjectCollection snowflakes = getObjectCollection("snowflake");

	for (int i = 0; i = snowflakes.objectCount; i++)
	{
		if (snowflakes.objectArray[i]->position.y < -(getViewplaneHeight() / 2.0f))
		{
			deleteObject(snowflakes.objectArray[i]);
			cout << "successfully deleted snowflake" << endl;
		}
		else if (snowflakes.objectArray[i]->position.y > (getViewplaneHeight() / 2.0f))
		{
			deleteObject(snowflakes.objectArray[i]);
			cout << "successfully deleted snowflake" << endl;
		}
		else if (snowflakes.objectArray[i]->position.x < -(getViewplaneWidth() / 2.0f))
		{
			deleteObject(snowflakes.objectArray[i]);
			cout << "successfully deleted snowflake" << endl;
		}
		else if (snowflakes.objectArray[i]->position.x > (getViewplaneWidth() / 2.0f))
		{
			deleteObject(snowflakes.objectArray[i]);
			cout << "successfully deleted snowflake" << endl;
		}
	}
}