#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H
#pragma once

#include <iostream>
#include <stdio.h>

#include <vector>

#include <GLEW\glew.h>
#include <SOIL\SOIL.h>

namespace Framework {
	namespace Utils {

		class TextureLoader {
		public:
			static unsigned int loadTexture2D(std::string path);
			static unsigned int loadCubeTexture(std::vector<std::string> faces);

		};

	}
}

#endif
