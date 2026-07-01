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
extern Texture gDefaultTexture;

using json = nlohmann::json;

#define COLOR_TO_CHAR(f) static_cast<unsigned char>(std::round(f * 255.0f))


class Material
{
public:
	std::string name = std::string("NakieHomu");
	std::string mFileName = std::string("NakieHomu");

	Shader* mShader;
	std::string shaderName;
	unsigned int diffuseTex;
	std::string diffuseTexPath;
	unsigned int maskTex;
	std::string maskTexPath;
	unsigned int normalTex;
	std::string normalTexPath;

	bool blendTransparent = false;

	glm::vec4 color = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec4 specColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	float specGloss = 0.05f;


	static glm::vec4 hexStringToColor(std::string input)
	{
		glm::vec4 ret(1.0f, 1.0f, 1.0f, 1.0f);

		if (input.empty())
			return ret;

		//std::cout << std::endl << "HEX: " << input << std::endl;

		std::vector<unsigned char> bytes = hex_to_bytes(input);

		if (bytes.size() < 3)
			return ret;

		ret.r = (float)bytes[0] / 255.0f;
		ret.g = (float)bytes[1] / 255.0f;
		ret.b = (float)bytes[2] / 255.0f;
		ret.a = (float)bytes[3] / 255.0f;

		//std::cout << std::endl << "HEX TO COLOR: " << std::endl
		//	<< " r: " << ret.r
		//	<< " g: " << ret.g
		//	<< " b: " << ret.b
		//	<< " a: " << ret.a
		//	<< std::endl;

		return ret;
	}


	static std::string packColor(glm::vec4 colorToPack)
	{

		unsigned char bytes[4] =
		{
			COLOR_TO_CHAR(colorToPack.r),
			COLOR_TO_CHAR(colorToPack.g),
			COLOR_TO_CHAR(colorToPack.b),
			COLOR_TO_CHAR(colorToPack.a)
		};

		std::string out = bytes_to_hex(bytes, 4);
		std::cout << std::endl << "PACKED: " << std::endl << std::hex << out << std::endl;

		return out;
	}

	Material(const char* fileName, bool createNew = false)
	{
		std::ifstream f(fileName);

		name = path_to_filename(fileName, true);
		mFileName = fileName;

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

		f.close();

		loadMatFile(fileName);
	};

	void loadMatFile(const char* fileName )
	{
		std::ifstream f(fileName);

		name = path_to_filename(fileName, true);
		mFileName = fileName;

		json matFile = json::parse(f);

		//matFile.parse();
		if (!matFile["shader"].empty())
		{
			shaderName = matFile["shader"].get<std::string>();
			mShader = new Shader(shaderName.c_str());
		}

		if (!matFile["color"].empty())
			color = hexStringToColor(matFile["color"].get<std::string>());

		if (!matFile["diffuseTex"].empty())
		{
			diffuseTexPath = matFile["diffuseTex"].get<std::string>();
			diffuseTex = loadTexture(diffuseTexPath.c_str());
		}

		if (!matFile["specColor"].empty())
			specColor = hexStringToColor(matFile["specColor"].get<std::string>());

		if (!matFile["specGloss"].empty())
			specGloss = matFile["specGloss"].get<float>();

		if (!matFile["blendTransparent"].empty())
			blendTransparent = matFile["blendTransparent"].get<bool>();
	}

	void reload()
	{
		loadMatFile(mFileName.c_str());
	}

	void createPlaceholderMaterial(const char* fileName)
	{
		std::string path = fileName;

		json matFile;
		matFile["diffuseTex"] = path;
		matFile["shader"] = "standard";

		matFile["color"] = packColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		matFile["specColor"] = packColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		matFile["specGloss"] = specGloss;
		matFile["blendTransparent"] = blendTransparent;

		std::ofstream out(path);
		out << std::setw(4) << matFile << std::endl;
	}

	void saveMaterial()
	{
		std::string path;
		path += mFileName;

		json matFile;
		matFile["shader"] = shaderName;
		matFile["diffuseTex"] = diffuseTexPath;
		matFile["color"] = packColor(color);
		matFile["specColor"] = packColor(specColor);
		matFile["specGloss"] = specGloss;
		matFile["blendTransparent"] = blendTransparent;

		std::ofstream out(path);
		out << std::setw(4) << matFile << std::endl;
		out.close();
	}


	void Set(glm::mat4 model)
	{
		if (!mShader)
			return;

		if (blendTransparent)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}

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
