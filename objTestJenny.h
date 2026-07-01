#pragma once
#ifndef _OBJTESTJENNY_H_
#define _OBJTESTJENNY_H_

#include "object.h"
#include "shader.h"
#include "model.h"
#include "awmodel.h"
#include <iostream>

#include "imstb_textedit.h"
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "imgui_stdlib.h"

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

		//writeALWModel(jennyModel, "./jenny.alwmdl");
	}

	void Draw()
	{
		if (!jennyModel)
			return;

		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, Position);
		model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::rotate(model, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));

		jennyModel->Draw(model);

		angle += gDeltaTime * 12.0f;
	}

	int meshIndex = 0;

	void DrawUI()
	{
		ImGui::Begin("Material Editor");
		ImGui::InputInt("Material Index:", &meshIndex, 1, 1);

		if (meshIndex >= jennyModel->meshes.size())
			meshIndex = 0;

		Mesh m = jennyModel->meshes[meshIndex];

		string fileName = m.material->mFileName.c_str();
		ImGui::Text(fileName.c_str());

		ImGui::InputText("shaderName", &m.material->shaderName);
		ImGui::InputText("diffuseTexPath", &m.material->diffuseTexPath);
		ImGui::ColorPicker4("Color", (float*)&m.material->color, ImGuiColorEditFlags_NoSmallPreview);
		ImGui::ColorPicker4("SpecColor", (float*)&m.material->specColor, ImGuiColorEditFlags_NoSmallPreview);
		ImGui::SliderFloat("SpecGloss", &m.material->specGloss, 0.1f, 100.0f);
		ImGui::Checkbox("blendTransparent", &m.material->blendTransparent);

		if (ImGui::Button("Save Material"))
		{
			//save
			m.material->saveMaterial();

			//reload
			m.material->reload();
		}

		if (ImGui::Button("Save All Materials"))
		{
			for (int i = 0; i < jennyModel->meshes.size(); i++)
			{
				//save
				jennyModel->meshes[i].material->saveMaterial();

				//reload
				jennyModel->meshes[i].material->reload();
			}
		}

		ImGui::End();
	}
};

#endif