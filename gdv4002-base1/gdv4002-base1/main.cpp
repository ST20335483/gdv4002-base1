#include "Engine.h"

// Function prototypes
void myUpdate(GLFWwindow* window, double tDelta);

int main(void) {

	// Initialise the engine (create window, setup OpenGL backend)
	int initResult = engineInit("GDV4002 - Applied Maths for Games", 1024, 1024, 25.0f);

	// If the engine initialisation failed report error and exit
	if (initResult != 0) {

		printf("Cannot setup game window!!!\n");
		return initResult; // exit if setup failed
	}

	//
	// Setup game scene objects here
	//
	// 
	//addObject("player1", glm::vec2(1.0f, 1.0f), glm::radians(45.0f), glm::vec2(0.5f, 1.0f), "Resources\\Textures\\truth-nuke.png", TextureProperties::NearestFilterTexture());

	addObject("Player1");
	addObject("Player2");

	GameObject2D* player1Object = getObject("Player1");

	if (player1Object != nullptr)
	{
		GameObject2D* player2Object = getObject("Player2");

		if (player2Object != nullptr) {

			player2Object->position = glm::vec2(1.5f, 1.0f);
			player2Object->orientation = glm::radians(45.0f);
			player2Object->size = glm::vec2(0.75f, 0.75f);
			player2Object->textureID = loadTexture("Resources\\Textures\\dog.png");
		}

		player1Object->position = glm::vec2(-1.0f, 1.0f);
		player1Object->orientation = glm::radians(30.0f);
		player1Object->size = glm::vec2(0.75f, 0.75f);
		player1Object->textureID = loadTexture("Resources\\Textures\\bumblebee.png");

		// update player1 here
	}

	setUpdateFunction(myUpdate);

	// Enter main loop - this handles update and render calls
	engineMainLoop();

	// When we quit (close window for example), clean up engine resources
	engineShutdown();

	// return success :)
	return 0;
}

void myUpdate(GLFWwindow* window, double tDelta)
{
	float player1RotationSpeed = glm::radians(90.0f);
	float playerVelocity = 2.0f;

	GameObject2D* player1 = getObject("Player1");
	player1->position += playerVelocity * tDelta;
	player1->orientation += player1RotationSpeed * tDelta;

}
