#include "TextureLoader.h"
#include "Logger.h"

namespace GF {
	namespace Utils {

		unsigned TextureLoader::loadTexture2D(const std::string& path) {
			GLuint handle;

			int
				width,
				height,
				bitsPerPixel;

			stbi_set_flip_vertically_on_load(1);
			unsigned char* image = stbi_load(path.c_str(), &width, &height, &bitsPerPixel, 4);

			glGenTextures(1, &handle);
			glBindTexture(GL_TEXTURE_2D, handle);

			//Creation hints
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

			//Provide OpenGL with the texture data
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

			//Generate mipmaps
			glEnable(GL_TEXTURE_2D);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			//Free local image data
			if (image == nullptr)
				Logger::log(Logger::LogType::ERROR_WARN, "Texture2D at '" + path + "' could not be loaded.");
			else
				stbi_image_free(image);

			return handle;
		}

		unsigned TextureLoader::loadCubeTexture(std::vector<std::string> texturesPaths) {
			GLuint handle;

			int
				width,
				height,
				bitsPerPixel;

			unsigned char* image = nullptr;

			glGenTextures(1, &handle);
			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_CUBE_MAP, handle);

			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

			for (unsigned i = 0; i < texturesPaths.size(); i++) {
				image = stbi_load(texturesPaths[i].c_str(), &width, &height, &bitsPerPixel, 4);

				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

				if (image == nullptr)
					Logger::log(Logger::LogType::ERROR_WARN, "TextureCube at '" + texturesPaths[i] + "' could not be loaded.");
				else
					stbi_image_free(image);
			}

			//Generate mipmaps
			glEnable(GL_TEXTURE_CUBE_MAP);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			return handle;
		}

	}
}