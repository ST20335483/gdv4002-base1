#pragma once

#include "GameObject2d.h"

class Missile : public GameObject2D
{

private:
	float angle;
	float velocity;
public:
	Missile(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float initialPhase, float initialPhaseVelocity);

	void update(double tDelta) override;

}; 