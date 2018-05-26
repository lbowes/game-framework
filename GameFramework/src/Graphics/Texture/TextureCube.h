#ifndef TEXTURECUBE_H
#define TEXTURECUBE_H
#pragma once

#include <vector>
#include <string>

#include "Texture.h"
#include "../../Core/Resource.hpp"

namespace Framework {
	namespace Graphics {

		class TextureCube : public Texture, public Resource {
		public:
			TextureCube(std::vector<std::string> textures, std::string resourceID);
			~TextureCube() = default;

			virtual void bind();
			virtual void unbind() const;

		};

	}
}

#endif
