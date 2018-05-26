#include "../Texture/Texture.h"

namespace Framework {
	namespace Graphics {

		int Texture::mCurrentlyBound = 0;

		Texture::Texture(const Texture& texture) {
			mHandle = texture.getHandle();
		}

	}
}