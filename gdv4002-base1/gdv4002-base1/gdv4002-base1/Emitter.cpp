#include "Emitter.h"
#include "Engine.h"
#include "Asteroid.h"
#include <random>
#include <complex>

using namespace std;

Emitter::Emitter(glm::vec2 initPosition, float initOriantation, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0)
{

	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;
	this->orientation = initOriantation;

	glm::vec2 scale = initSize;

	particleNumber = 0;

	for (int i = 0; i < 8; i++)
	{
		string path = "Resources\\Textures\\asteroid" + string(".png");
		asteroids[i] = loadTexture(path.c_str());
	}

	float pi = 3.14159f;

	random_device rd;

	gen = mt19937(rd());

	spriteDist = uniform_int_distribution<int>(0, 7);
	normDist = uniform_real_distribution<float>(-2.0f, 2.0f);
	massDist = uniform_real_distribution<float>(0.005f, 0.08f);
	scaleDist = uniform_real_distribution<float>(0.25f, 0.5f);
	rotateDist = uniform_real_distribution<float>(0.0f, 360.0f);
}

void Emitter::render()
{

}

void Emitter::update(double tDelta)
{
	orientation += (float)tDelta;

	emitCounter += (float)tDelta / 50;

	while (emitCounter >= emitTimeInterval)
	{
		emitCounter -= emitTimeInterval;

		float x = position.x + normDist(gen) * size.x;
		float y = position.y + normDist(gen) * size.y;
		float scale = scaleDist(gen);
		float mass = massDist(gen);
		float orientation = rotateDist(gen) * (scaleDist(gen) * 10) * (normDist(gen) * 10);
		int spriteIndex = spriteDist(gen);

		Asteroid* s1 = new Asteroid(glm::vec2(x, y), orientation, glm::vec2(scale, scale), asteroids[spriteIndex], mass);
		string key = string("Asteroid");

		if (particleNumber > 0)
		{
			key += to_string(particleNumber);
		}

		particleNumber++;

		addObject(key.c_str(), s1);
	}
}