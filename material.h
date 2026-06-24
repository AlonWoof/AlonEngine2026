#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "shader.h"

#include <Windows.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

typedef struct
{
	unsigned char shaderNameSize;
	const char* shaderName;
	glm::vec4 matColor;

	unsigned int diffuseTexNameSize;
	const char* diffuseTexName;

	unsigned int maskTexNameSize;
	const char* maskTexName;

	unsigned int normalTexNameSize;
	const char* normalTexName;
}MatFile;

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

	};
};


#endif // !_MATERIAL_H_
