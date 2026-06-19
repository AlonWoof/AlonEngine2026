#pragma once
#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

unsigned int loadTexture(char const* path);

#endif // !_TEXTURE_H_
