#include "Texture2D.h"
#include "TextureLoader.h"

namespace GF {
	namespace Graphics {

		Texture2D::Texture2D(const std::string& path, const std::string& resID) :
			Resource(resID)
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