#pragma once
#ifndef _MODEL_H_
#define _MODEL_H_

#include "gfx.h"
#include "mesh.h"
#include "material.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

class Model
{
public:
	vector<Texture> textures_loaded;
	vector<Material> mats;
	vector<Mesh> meshes;

	Model(string const& path, bool gamma = false)// : gammaCorrection(gamma)
	{
		//loadModel(path);
	}

	void loadModel(string const& path)
	{

	}
};


#endif