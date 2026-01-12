#include "GameObject2D.h"
#include "Asteroid.h"
#include "Emitter.h"
#include <complex>

using namespace std;

Asteroid::Asteroid(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);
	this->size = initSize;
	this->orientation = initOrientation;
}

void Asteroid::update(double tDelta) {

	static float asteroidRotationSpeed = glm::radians(20.0f);
	GameObject2D::orientation += asteroidRotationSpeed * (float)tDelta;
	float asteroidDirection = asteroidRotationSpeed * (float)tDelta * 1.5;

	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> dir = exp(i * orientation * (float)tDelta);

	velocity = glm::vec2(dir.real() * 15, dir.imag() * 15);

	position = position + velocity * (float)tDelta * glm::vec2(0.1f, 0.1f);
}