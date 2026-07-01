#pragma once
#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "gfx.h"
#include "light.h"
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
extern Light gDirLight;
extern glm::vec3 gAmbientLight;
extern Camera gCamera;

using json = nlohmann::json;

#define COLOR_TO_CHAR(f) static_cast<unsigned char>(std::round(f * 255.0f))


class Material
{
public:
	std::string name = std::string("NakieHomu");

	Shader* mShader;
	std::string shaderName;
	unsigned int diffuseTex;
	std::string diffuseTexPath;
	unsigned int maskTex;
	std::string maskTexPath;
	unsigned int normalTex;
	std::string normalTexPath;

	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 specColor = glm::vec3(0.0f, 0.0f, 0.0f);
	float specGloss = 0.01f;

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

	Material(const char* fileName, bool createNew = false)
	{
		std::ifstream f(fileName);

		name = path_to_filename(fileName,true);

		if (!f.is_open() && !createNew)
		{
			mShader = new Shader("default");
			std::cout << "	ERROR OPENING " << fileName << " !" << std::endl;
			return;
		}
		else if (!f.is_open())
		{
			mShader = new Shader("default");
			std::cout << "	CREATED PLACEHOLDER MATERIAL: " << fileName << std::endl;
			createPlaceholderMaterial(fileName);
			return;
		}



		json matFile = json::parse(f);

		//matFile.parse();
		mShader = new Shader(matFile["shader"].get<std::string>().c_str());
		color = hexStringToColor(matFile["color"].get<std::string>());
		diffuseTex = loadTexture(matFile["diffuseTex"].get<std::string>().c_str());
		//writeMaterialToFile("TEST");
	};

	void createPlaceholderMaterial(const char* fileName)
	{
		std::string path = fileName;

		json matFile;
		matFile["diffuseTex"] = path;
		matFile["shader"] = "standard";

		matFile["color"] = int_to_hex(packColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)));
		std::ofstream out(path);
		out << std::setw(4) << matFile << std::endl;
	}

	void writeMaterialToFile()
	{
		std::string path;
		path += "./data/materials/";

		CreateDirectory(std::wstring(path.begin(), path.end()).c_str(), NULL);

		path += name;
		path += ".mat";

		json matFile;
		matFile["diffuseTex"] = diffuseTexPath;
		matFile["shader"] = "standard";

		glm::vec4 testColor(0.25f, 0.5f, 1.0f, 1.0f);
		matFile["color"] = int_to_hex(packColor(testColor));

		std::cout << matFile << std::endl;
		std::ofstream out(path);

		out << std::setw(4) << matFile << std::endl;

		hexStringToColor(matFile["color"].get<std::string>());
		
	};

	void Set(glm::mat4 model)
	{
		if (!mShader)
			return;

		mShader->use();
		mShader->setMat4("projection", gProjectionMatrix);
		mShader->setMat4("view", gViewMatrix);
		mShader->setMat4("model", model);
		mShader->setVec3("viewPos", gCamera.Position);

		mShader->setVec4("color", color);

		mShader->setVec3("dirLight.direction", gDirLight.Direction);
		mShader->setVec3("dirLight.color", gDirLight.Color);
		mShader->setVec3("ambient", gAmbientLight);
		mShader->setFloat("specGloss", specGloss);
		mShader->setVec3("specColor", specColor);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, diffuseTex);

	}


};


#endif // !_MATERIAL_H_
