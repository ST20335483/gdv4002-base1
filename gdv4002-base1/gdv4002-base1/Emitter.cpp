#include "Emitter.h"
#include "Engine.h"
#include "Snowflake.h"
#include <random>
#include <complex>

using namespace std;

Emitter::Emitter(glm::vec2 initPosition, glm::vec2 initSize, float emitTimeInterval) : GameObject2D(initPosition, 0.0f, initSize, 0)
{

	this->emitTimeInterval = emitTimeInterval;
	emitCounter = emitTimeInterval;

	particleNumber = 0;

	for (int i = 0; i < 8; i++)
	{
		string path = "Resources\\Textures\\asteroid" + string(".png");
		snowflakes[i] = loadTexture(path.c_str());

		if (snowflakes[i] > 0)
			cout << "successfully loaded texture " << path << endl;
		else
			cout << "failed to load texture " << path << endl;
	}

	float pi = 3.14159f;

	random_device rd;

	gen = mt19937(rd());

	spriteDist = uniform_int_distribution<int>(0, 7);
	normDist = uniform_real_distribution<float>(-1.0f, 1.0f);
	massDist = uniform_real_distribution<float>(0.005f, 0.08f);
	scaleDist = uniform_real_distribution<float>(0.8f, 0.8f);
}

void Emitter::render()
{

}

void Emitter::update(double tDelta)
{
	emitCounter += (float)tDelta / 50;

	while (emitCounter >= emitTimeInterval)
	{
		emitCounter -= emitTimeInterval;

		float x = position.x + normDist(gen) * size.x;
		float y = position.y + normDist(gen) * size.y;
		float scale = scaleDist(gen);
		float mass = massDist(gen);
		float rotationSpeed = glm::radians(normDist(gen) * 45.0f);
		int spriteIndex = spriteDist(gen);

		Snowflake* s1 = new Snowflake(glm::vec2(x, y), 0.0f, glm::vec2(scale, scale), snowflakes[spriteIndex], mass, rotationSpeed);
		string key = string("Snowflake");

		if (particleNumber > 0)
		{
			key += to_string(particleNumber);
		}

		particleNumber++;

		addObject(key.c_str(), s1);
	}
}