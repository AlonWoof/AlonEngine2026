#pragma once
#ifndef _OBJTESTJENNY_H_
#define _OBJTESTJENNY_H_

#include "object.h"
#include "shader.h"
#include "model.h"
#include "awmodel.h"
#include <iostream>

class ObjectTestJenny : public Object
{
public:

	Model* jennyModel;
	Material* material;
	float angle = 0.0f;

	ObjectTestJenny(glm::vec3 nPos = glm::vec3(0.0f, 0.0f, 0.0f))
	{
		Init(nPos, glm::vec3(0, 0, 0));

		jennyModel = new Model("./data/models/JenniferDehan/JenniferDehan.fbx");
		material = new Material("./data/materials/test.mat");

		writeALWModel(jennyModel, "./jenny.alwmdl");
	}

	void Draw()
	{
		if (!jennyModel)
			return;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, Position);
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 1.0f, 1.0f));

		jennyModel->Draw(model);
	}
};

#endif