#ifndef UTILS_TEXTURELOADER_H
#define UTILS_TEXTURELOADER_H
#pragma once

#include "Vendor/stb_image/stb_image.h"

#include <vector>
#include <stdio.h>
#include <GL/glew.h>
#include <string>

namespace GF {
	namespace Utils {

		class TextureLoader {
		public:
			static unsigned loadTexture2D(const std::string& path);
			static unsigned loadCubeTexture(std::vector<std::string> faces);

		};

	}
}

#endif
