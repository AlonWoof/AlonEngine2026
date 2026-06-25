#pragma once
#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "gfx.h"

enum LIGHT_TYPE
{
	LIGHT_DIRECTIONAL,
	LIGHT_POINT,
	LIGHT_SPOT
};

class Light
{
public:
	LIGHT_TYPE type;

	glm::vec3 Position;
	glm::vec3 Rotation;
	glm::vec3 Direction;

	glm::vec3 Color = glm::vec3(1.0f, 1.0f, 1.0f);
	float intensity = 1.0f;
};

#endif