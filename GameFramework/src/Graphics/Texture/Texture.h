#ifndef TEXTURE_H
#define TEXTURE_H
#pragma once

#include "Utils/TextureLoader.h"

namespace Framework {
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
