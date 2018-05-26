#include "Texture2D.h"
#include "Utils/TextureLoader.h"

namespace Framework {
	namespace Graphics {

		Texture2D::Texture2D(std::string path, std::string resourceID) :
			Resource(resourceID)
		{ 
			mHandle = Utils::TextureLoader::loadTexture2D(path);
		}

		void Texture2D::bind() {
			if (mCurrentlyBound == this->mHandle)
				return;

			glBindTexture(GL_TEXTURE_2D, mHandle);
			mCurrentlyBound = this->mHandle;
		}

		void Texture2D::unbind() const {
			glBindTexture(GL_TEXTURE_2D, 0);
			mCurrentlyBound = 0;
		}

	}
}