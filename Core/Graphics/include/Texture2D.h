#ifndef GRAPHICS_TEXTURE2D_H
#define GRAPHICS_TEXTURE2D_H
#pragma once

#include <string>

#include "Texture.h"
#include "Resource.hpp"

namespace GF {
	namespace Graphics {

		class Texture2D : public Texture, public Resource {
		public:
			Texture2D(const std::string& path, const std::string& resID);
			~Texture2D() = default;

			virtual void bind();
			virtual void unbind() const;

		};

	}
}

#endif
