#include "TextureLoader.h"
#include "ConsoleLogger.h"

namespace Framework {
	namespace Utils {

		unsigned int TextureLoader::loadTexture2D(std::string path) {
			GLuint textureHandle;
			int width, height;
			unsigned char* image = SOIL_load_image(path.c_str(), &width, &height, 0, SOIL_LOAD_RGB);
			
			glGenTextures(1, &textureHandle);
			glBindTexture(GL_TEXTURE_2D, textureHandle);

			if (image == 0)
				ConsoleLogger::log(ConsoleLogger::LogType::ERROR_WARN, "Texture2D at '" + path + "' could not be loaded.");
			
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

			glEnable(GL_TEXTURE_2D);
			glGenerateMipmap(GL_TEXTURE_2D);

			glBindTexture(GL_TEXTURE_2D, 0);

			SOIL_free_image_data(image);

			return textureHandle;
		}

		unsigned int TextureLoader::loadCubeTexture(std::vector<std::string> texturesPaths) {
			GLuint textureHandle;
			int 
				width, 
				height;
			unsigned char* image;
			
			glGenTextures(1, &textureHandle);
			glActiveTexture(GL_TEXTURE0);

			glBindTexture(GL_TEXTURE_CUBE_MAP, textureHandle);
			
			for (unsigned int i = 0; i < texturesPaths.size(); i++) {
				image = SOIL_load_image(texturesPaths[i].c_str(), &width, &height, 0, SOIL_LOAD_RGB);
				if (image == 0)
					ConsoleLogger::log(ConsoleLogger::LogType::ERROR_WARN, "TextureCube at '" + texturesPaths[i] + "' could not be loaded.");
				
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
				SOIL_free_image_data(image);
			}
			
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
			
			glEnable(GL_TEXTURE_CUBE_MAP);
			glGenerateMipmap(GL_TEXTURE_CUBE_MAP);

			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

			return textureHandle;
		}

	}
}