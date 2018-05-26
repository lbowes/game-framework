#include "TextureCube.h"
#include "Utils/TextureLoader.h"

namespace Framework {
	namespace Graphics {

		TextureCube::TextureCube(std::vector<std::string> paths, std::string resourceID) :
			Resource(resourceID)
		{
			mHandle = Utils::TextureLoader::loadCubeTexture(paths);
		}

		void TextureCube::bind() {
			if (mCurrentlyBound == this->mHandle)
				return;

			glBindTexture(GL_TEXTURE_CUBE_MAP, mHandle);
			mCurrentlyBound = this->mHandle;
		}

		void TextureCube::unbind() const {
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
			mCurrentlyBound = 0;
		}

	}
}