#pragma once
#ifndef _AWMODEL_H_
#define _AWMODEL_H_

#include "model.h"
#include "mesh.h"
#include <iostream>

using namespace std;


void writeALWMesh(ofstream* outfile, Mesh* mesh)
{
	outfile->write(mesh->material->name.c_str(), sizeof(mesh->material->name.size()));

	int numVerts = mesh->vertices.size();
	int numIndex = mesh->indices.size();

	outfile->write(reinterpret_cast<const char*>(&numVerts), sizeof(numVerts));
	for (int i = 0; i < mesh->vertices.size(); i++)
	{
		outfile->write(reinterpret_cast<const char*>(&mesh->vertices[i]), sizeof(mesh->vertices[i]));
	}

	outfile->write(reinterpret_cast<const char*>(&numIndex), sizeof(numIndex));
	for (int i = 0; i < mesh->indices.size(); i++)
	{
		outfile->write(reinterpret_cast<const char*>(&mesh->indices[i]), sizeof(mesh->indices[i]));
	}

}

void writeALWModel(Model* modelToWrite, const char* fileName)
{
	ofstream outfile;
	outfile.open(fileName, ios::out | ios::binary);

	if (!outfile)
	{
		cout << "FILE PATH " << fileName << " IS INVALID!";
		return;
	}

	//Write mesh data
	int numMeshes = modelToWrite->meshes.size();
	outfile.write(reinterpret_cast<const char*>(&numMeshes), sizeof(numMeshes));

	for (int i = 0; i < numMeshes; i++)
	{
		writeALWMesh(&outfile, &modelToWrite->meshes[i]);
	}

	outfile.close();
}





#endif