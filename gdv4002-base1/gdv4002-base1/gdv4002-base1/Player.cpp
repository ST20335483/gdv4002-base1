#include "Player.h"
#include "Bullet.h"
#include "Keys.h"
#include "Engine.h"
#include "GameObject2D.h"
#include <bitset>
#include <complex>

using namespace std;
using std::complex;
extern std::bitset<5> keys;

Player::Player(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID, float mass, float thrust) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	this->mass = mass;
	this->thrust = thrust;
	velocity = glm::vec2(0.0f, 0.0f);

	bulletSpacing = true;

	particleNumber = 0;

	for (int i = 0; i < 8; i++)
	{
		string path = "Resources\\Textures\\missile" + string(".png");
		bullets[i] = loadTexture(path.c_str());
	}
}

void Player::update(double tDelta)
{
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> dir = exp(i * GameObject2D::orientation);
	static float playerTurnSpeed = glm::radians(180.0f);

	glm::vec2 F = glm::vec2(0.0f, 0.0f);

	if (keys.test(Key::W) == true)
	{
		F += glm::vec2(dir.real(), dir.imag()) * thrust;
	}
	if (keys.test(Key::S) == true)
	{
		F -= glm::vec2(dir.real(), dir.imag()) * thrust;
	}
	if (keys.test(Key::A) == true)
	{
		GameObject2D::orientation += playerTurnSpeed * (float)tDelta;
	}
	if (keys.test(Key::D) == true)
	{
		GameObject2D::orientation -= playerTurnSpeed * (float)tDelta;
	}

	glm::vec2 accel = F * (1.0f / mass);
	velocity = velocity + (accel * (float)tDelta);
	position = position + (velocity * (float)tDelta);

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

	float x = position.x;
	float y = position.y;
	float bulletScale = 0.2f;
	GLuint missileTexture = loadTexture("Resources\\Textures\\missile.png");

	if (keys.test(Key::SPACE) == false)
		bulletSpacing = true;

	if (keys.test(Key::SPACE) == true && bulletSpacing == true)
	{
		Bullet* s1 = new Bullet(glm::vec2(x, y), Player::orientation, glm::vec2(bulletScale, bulletScale), missileTexture);
		string key = string("Bullet");

		if (particleNumber > 0)
		{
			key += to_string(particleNumber);
		}

		particleNumber++;

		addObject(key.c_str(), s1);
		bulletSpacing = false;
	}
}
