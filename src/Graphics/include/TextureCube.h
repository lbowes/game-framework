#ifndef GRAPHICS_TEXTURECUBE_H
#define GRAPHICS_TEXTURECUBE_H
#pragma once

#include <vector>
#include <string>

#include "Texture.h"
#include "Resource.hpp"

namespace GF {
	namespace Graphics {

		class TextureCube : public Texture, public Resource {
		public:
			TextureCube(std::vector<std::string> textures, const std::string& resID);
			~TextureCube() = default;

			virtual void bind();
			virtual void unbind() const;

		};

	}
}

#endif
