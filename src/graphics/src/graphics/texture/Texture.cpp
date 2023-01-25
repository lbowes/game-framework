#include "Texture.h"

namespace GF {
	namespace Graphics {

		int Texture::mCurrentlyBound = 0;

		Texture::Texture(const Texture& texture) {
			mHandle = texture.getHandle();
		}

	}
}