#include "Enemy.h"
#include "GameObject2D.h"
#include <complex>
#include <cstdlib>
#include <iostream>
#include "Engine.h"

using std::complex;

Enemy::Enemy(
	glm::vec2 initPosition,
	float initOrientation,
	glm::vec2 initSize,
	GLuint initTextureID,
	float initialPhase,
	float initialPhaseVelocity,
	float enemyRadiansValue)
	: GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	phaseAngle = initialPhase;
	phaseVelocity = initialPhaseVelocity;
	enemyRadians = enemyRadiansValue;
}

void Enemy::update(double tDelta)
{
	complex<float> i = complex<float>(0.0f, 1.0f);
	complex<float> dir = exp(i * enemyRadians);

	position.x += dir.real()/3 * tDelta;
	position.y += dir.imag()/3 * tDelta;

	if (position.y < -getViewplaneHeight() / 2.0f)
	{
		position.y = (getViewplaneHeight() / 2.0f);
	}
	if (position.y > getViewplaneHeight() / 2.0f)
	{
		position.y = (-getViewplaneHeight() / 2.0f);
	}
	if (position.x < -getViewplaneWidth() / 2.0f)
	{
		position.x = (getViewplaneWidth() / 2.0f);
	}
	if (position.x > getViewplaneWidth() / 2.0f)
	{
		position.x = (-getViewplaneWidth() / 2.0f);
	}

	static float enemyRotationSpeed = glm::radians(10.0f);
	GameObject2D::orientation += enemyRotationSpeed * tDelta;
}