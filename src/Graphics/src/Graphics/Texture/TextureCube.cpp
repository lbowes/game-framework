#include "TextureCube.h"
#include "TextureLoader.h"

namespace GF {
	namespace Graphics {

		TextureCube::TextureCube(std::vector<std::string> paths, const std::string& resID) :
			Resource(resID)
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