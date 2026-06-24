#pragma once
#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "gfx.h"
#include <iostream>

//Copyright 2026 Jennifer Haden

extern float gDeltaTime;

class Object
{
public:

	glm::vec3 Position;
	glm::vec3 Rotation;

	Object(glm::vec3 nPos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 nRot = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		Init(nPos, nRot);
	}

	virtual void Init(glm::vec3 nPos, glm::vec3 nRot)
	{
		Position = nPos;
		Rotation = nRot;
	}

	virtual void Update()
	{
		//Code for updates here
		std::cout << "I'm here too lol" << std::endl;
	}

	virtual void Draw()
	{
		//Code for rendering here.
	}

	void setPosition(glm::vec3 nPos) { Position = nPos; };
	void setRotation(glm::vec3 nRot) { Rotation = nRot; };

protected:

	
};

#endif // !_OBJECT_H_
