#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "shader.h"

#include <tinyxml2.h>
#include <Windows.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>


class Material
{
public:
	Shader* mShader;
	unsigned int diffuseTex;
	unsigned int maskTex;
	unsigned int normalTex;

	glm::vec4 color;
	glm::vec3 specColor;
	float shininess;

	Material()
	{
		mShader = new Shader("default");
		writeMaterialToFile("TEST");
	};

	void writeMaterialToFile(const char* fileName)
	{
		std::string path;
		path += "./data/materials/";

		CreateDirectory(std::wstring(path.begin(), path.end()).c_str(), NULL);

		path += fileName;
		path += ".mat";

		tinyxml2::XMLDocument* matFile = new tinyxml2::XMLDocument();
		tinyxml2::XMLElement* rootElement = matFile->NewElement("Material");
		tinyxml2::XMLElement* shaderElement = rootElement->InsertNewChildElement("Shader");
		shaderElement->SetText("default");

		tinyxml2::XMLElement* diffuseTexElement = rootElement->InsertNewChildElement("diffuseTex");
		diffuseTexElement->SetText("./data/textures/NakieHomu.png");

		tinyxml2::XMLElement* maskTexElement = rootElement->InsertNewChildElement("maskTex");
		maskTexElement->SetText("./data/textures/NakieHomu.png");

		tinyxml2::XMLElement* normalTexElement = rootElement->InsertNewChildElement("normalTex");
		normalTexElement->SetText("./data/textures/NakieHomu.png");

		matFile->Print();

		tinyxml2::XMLPrinter streamer;
		matFile->Print(&streamer);

		std::cout << streamer.CStr() << std::endl;

	};
};


#endif // !_MATERIAL_H_
