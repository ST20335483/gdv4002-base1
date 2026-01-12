#include "Missile.h"
#include <complex>

Missile::Missile(
	glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initialPhase,
	float initialPhaseVelocity)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	angle = initOrientation;
	velocity = initialPhaseVelocity;
}

void Missile::update(double tDelta)
{
	std::complex<float> i = std::complex<float>(0.0f, 1.0f);
	std::complex<float> dir = exp(i * GameObject2D::orientation);


}