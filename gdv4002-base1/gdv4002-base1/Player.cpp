#include "Player.h"
#include "Keys.h"
#include "Engine.h"
#include <bitset>
#include <complex>

extern std::bitset<5> keys;
extern glm::vec2 gravity;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float thrust) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;
	this->thrust = thrust;
	velocity = glm::vec2(0.0f, 0.0f);
}

void Player::update(double tDelta)
{
	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	if (keys.test(Key::W) == true)
	{
		F += glm::vec2(0.0f, thrust);
	}
	if (keys.test(Key::S) == true)
	{
		F += glm::vec2(0.0f, -thrust);
	}
	if (keys.test(Key::A) == true)
	{
		F += glm::vec2(-thrust, 0.0f);
	}
	if (keys.test(Key::D) == true)
	{
		F += glm::vec2(thrust, 0.0f);
	}

	F += gravity;

	if (position.y < -getViewplaneHeight() / 2.0f)
	{
		//F += glm::vec2(0.0f, 20.0f);
		position.y = (getViewplaneHeight() / 2.0f);
	}
	if (position.y > getViewplaneHeight() / 2.0f)
	{
		//F += glm::vec2(0.0f, -20.0f);
		position.y = (-getViewplaneHeight() / 2.0f);
	}
	if (position.x < -getViewplaneWidth() / 2.0f)
	{
		//F += glm::vec2(20.0f, 0.0f);
		position.x = (getViewplaneWidth() / 2.0f);
	}
	if (position.x > getViewplaneWidth() / 2.0f)
	{
		//F += glm::vec2(-20.0f, 0.0f);
		position.x = (-getViewplaneWidth() / 2.0f);
	}

	glm::vec2 a = F * (1.0f / mass);

	velocity = velocity + (a * (float)tDelta);

	position = position + (velocity * (float)tDelta);
}
