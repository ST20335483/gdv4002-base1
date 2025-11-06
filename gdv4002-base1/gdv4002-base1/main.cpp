#include "Engine.h"
#include "Keys.h"
#include <bitset>
#include <complex>

// Function prototypes
using std::cout;
using std::endl;

std::bitset<5> keys{ 0x0 };

void myUpdate(GLFWwindow* window, double tDelta);

void myKeyboardHandler(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 10.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	addObject("player", glm::vec2(-1.5f, 0.0f), 0.0f, glm::vec2(0.5f, 0.5f), "Resources\\Textures\\player1_ship.png");
	addObject("enemy", glm::vec2(0.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\dog.png");
	addObject("enemy", glm::vec2(1.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\dog.png");
	addObject("enemy", glm::vec2(2.0f, 0.0f), 0.0f, glm::vec2(0.75f, 0.75f), "Resources\\Textures\\dog.png");

	setUpdateFunction(myUpdate);
	setKeyboardHandler(myKeyboardHandler);

	listGameObjectKeys();

	listObjectCounts();

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

float enemyPhase[3] = { -1.0f, 1.0f, -1.0f };
float enemyPhaseVelocity[3] = { glm::radians(90.0f), glm::radians(90.0f), glm::radians(90.0f) };


void myUpdate(GLFWwindow* window, double tDelta)
{
	GameObjectCollection enemies = getObjectCollection("enemy");
	for (int i = 0; i < enemies.objectCount; i++)
	{
		enemies.objectArray[i]->position.y = (sinf(enemyPhase[i] * 1.5));
		enemyPhase[i] += enemyPhaseVelocity[i] * tDelta;
	}

	GameObject2D* player = getObject("player");
	static float playerSpeed = 5.0f;

	std::complex<float> i = std::complex<float>(0.0f, 1.0f);

	std::complex<float> dir = exp(i * player->orientation);

	static float playerTurnSpeed = glm::radians(180.0f);
	
	if (keys.test(Key::W) == true)
		player->position += glm::vec2(dir.real(), dir.imag()) * (float)tDelta;

	if (keys.test(Key::S) == true)
		player->position -= glm::vec2(dir.real(), dir.imag()) * (float)tDelta;

	if (keys.test(Key::A) == true)
		player->orientation += playerTurnSpeed * (float)tDelta;

	if (keys.test(Key::D) == true)
		player->orientation -= playerTurnSpeed * (float)tDelta;
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
		}
	}
}
