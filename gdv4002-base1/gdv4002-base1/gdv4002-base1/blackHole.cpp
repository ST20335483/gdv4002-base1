#include "Keys.h"
#include "Engine.h"
#include "GameObject2D.h"
#include <bitset>
#include <complex>
#include "blackHole.h"

BlackHole::BlackHole(glm::vec2 initPosition, float initOrientation, glm::vec2 initSize, GLuint initTextureID) : GameObject2D(initPosition, initOrientation, initSize, initTextureID)
{
	velocity = glm::vec2(0.0f, 0.0f);
}

void BlackHole::update(double tDelta)
{
	GameObject2D::orientation += glm::radians(15.0f) * (float)tDelta;
}