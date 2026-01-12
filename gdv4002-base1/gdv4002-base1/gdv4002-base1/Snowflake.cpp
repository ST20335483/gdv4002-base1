#include "GameObject2D.h"
#include "Snowflake.h"
#include <random>
#include <complex>

using namespace std;

Snowflake::Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {
	
	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);

	this->angleChangePerSecond = angleChangePerSecond;
}

void Snowflake::update(double tDelta) {

	orientation += angleChangePerSecond * (float)tDelta;
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> dir = exp(i * orientation);

	glm::vec2 gravity = glm::vec2(dir.real() / 2000, dir.imag() / 2000);

	glm::vec2 accel = gravity * (1.0f / mass);

	velocity = (velocity + accel * ((float)tDelta * 20));

	position = position + velocity * (float)tDelta;

	
}