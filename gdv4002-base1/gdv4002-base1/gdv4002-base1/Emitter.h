#pragma once
#include "GameObject2D.h"
#include <random>

class Emitter : public GameObject2D
{
private:
	float emitTimeInterval;
	float emitCounter;
	float scale;

	unsigned long long particleNumber;

	GLuint asteroids[8];

	std::mt19937 gen;

	std::uniform_int_distribution<int> spriteDist;
	std::uniform_real_distribution<float> normDist;
	std::uniform_real_distribution<float> massDist, scaleDist, rotateDist;

public:
	Emitter(glm::vec2 initPosition, float initOriantation, glm::vec2 initSize, float emitTimeInterval);

	void update(double tDelta) override;
	void render() override;
};