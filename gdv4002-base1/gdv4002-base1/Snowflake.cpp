#include "Snowflake.h"

extern glm::vec2 gravity;

Snowflake::Snowflake(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float angleChangePerSecond) : GameObject2D(initPosition, initOrientation, initSize, initTextureID) {
	
	this->mass = mass;
	velocity = glm::vec2(0.0f, 0.0f);

	this->angleChangePerSecond = angleChangePerSecond;
}

void Snowflake::update(double tDelta) {

	glm::vec2 F = gravity;

	glm::vec2 accel = F * (1.0f / mass);

	velocity = velocity + accel * (float)tDelta;

	position = position + velocity * (float)tDelta;

	orientation += angleChangePerSecond * (float)tDelta;
}