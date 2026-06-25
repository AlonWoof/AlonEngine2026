#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "shader.h"
#include "utility.h"
#include <json.hpp>
#include <Windows.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include <ctime>

extern glm::mat4 gProjectionMatrix;
extern glm::mat4 gViewMatrix;

using json = nlohmann::json;

#define COLOR_TO_CHAR(f) static_cast<unsigned char>(std::round(f * 255.0f))

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

	static glm::vec4 hexStringToColor(std::string input)
	{
		glm::vec4 ret(1.0f, 1.0f, 1.0f, 1.0f);

		std::cout << std::endl << "HEX: " << input << std::endl;

		std::vector<unsigned char> bytes = hex_to_bytes(input);

		ret.r = (float)bytes[0] / 255.0f;
		ret.g = (float)bytes[1] / 255.0f;
		ret.b = (float)bytes[2] / 255.0f;
		ret.a = (float)bytes[3] / 255.0f;

		std::cout << std::endl << "HEX TO COLOR: " << std::endl
			<< " r: " << ret.r
			<< " g: " << ret.g
			<< " b: " << ret.b
			<< " a: " << ret.a
			<< std::endl;

		return ret;
	}


	static int packColor(glm::vec4 colorToPack)
	{

		unsigned char bytes[4] =
		{
			COLOR_TO_CHAR(colorToPack.a),
			COLOR_TO_CHAR(colorToPack.b),
			COLOR_TO_CHAR(colorToPack.g),
			COLOR_TO_CHAR(colorToPack.r)
		};

		int32_t out;
		std::memcpy(&out, bytes, sizeof(out));
		std::cout << std::endl << "PACKED: " << std::endl << std::hex << out << std::endl;
		return out;
	}

	Material(const char* fileName)
	{
		std::ifstream f(fileName);
		json matFile = json::parse(f);

		//matFile.parse();
		mShader = new Shader(matFile["shader"].get<std::string>().c_str());
		color = hexStringToColor(matFile["color"].get<std::string>());
		diffuseTex = loadTexture(matFile["diffuseTex"].get<std::string>().c_str());
		//writeMaterialToFile("TEST");
	};

	void writeMaterialToFile(const char* fileName)
	{
		std::string path;
		path += "./data/materials/";

		CreateDirectory(std::wstring(path.begin(), path.end()).c_str(), NULL);

		path += fileName;
		path += ".mat";

		json matFile;
		matFile["diffuseMap"] = "NakieHomura.png";
		matFile["shader"] = "default";


		glm::vec4 testColor(0.25f, 0.5f, 1.0f, 1.0f);
		matFile["color"] = int_to_hex(packColor(testColor));

		std::cout << matFile << std::endl;
		std::ofstream out(path);

		out << std::setw(4) << matFile << std::endl;

		hexStringToColor(matFile["color"].get<std::string>());
		
	};

	void Set(glm::mat4 model)
	{
		mShader->use();
		mShader->setMat4("projection", gProjectionMatrix);
		mShader->setMat4("view", gViewMatrix);
		mShader->setMat4("model", model);
		mShader->setVec4("color", color);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTex);

	}


	void loadMaterial()
	{

	}

};


#endif // !_MATERIAL_H_
