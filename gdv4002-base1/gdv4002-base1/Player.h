#pragma once
#include "GameObject2D.h"

class Player : public GameObject2D
{

private:
	float mass;
	glm::vec2 velocity;
	float thrust;

public:
	Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float thrust);

	void update(double tDelta) override;


};
