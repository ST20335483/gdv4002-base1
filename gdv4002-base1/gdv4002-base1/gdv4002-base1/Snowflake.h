#pragma once
#include "GameObject2D.h"
#include <random>

class Snowflake : public GameObject2D {

private:
	float mass;
	glm::vec2 velocity;
	float angleChangePerSecond;

	std::mt19937 gen;
	std::uniform_real_distribution<float> randomAngle;

public:
	Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond);

	void update(double tDelta) override;
};