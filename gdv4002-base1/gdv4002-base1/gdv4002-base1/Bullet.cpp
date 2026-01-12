#include "GameObject2D.h"
#include "Bullet.h"
#include <random>
#include <complex>

using namespace std;

Bullet::Bullet(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {

	velocity = glm::vec2(0.0f, 0.0f);

	this->position = initPosition;
	
	this->size = initSize;
}

void Bullet::update(double tDelta) {

	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> dir = exp(i * orientation);

	velocity = glm::vec2(dir.real() * 3, dir.imag() * 3);
	position = position + velocity * (float)tDelta;
}