#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H
#pragma once

#include "TextureLoader.h"

namespace GF {
	namespace Graphics {

		class Texture {
		protected:
			static int mCurrentlyBound;
			int mHandle = 0;

		public:
			Texture() = default;
			Texture(const Texture& texture);
			virtual ~Texture() = default;

			inline int getHandle() const { return mHandle; }

			virtual void bind() = 0;
			virtual void unbind() const = 0;

		};

	}
}

#endif
