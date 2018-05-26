#ifndef TEXTURE2D_H
#define TEXTURE2D_H
#pragma once

#include <string>

#include "Texture.h"
#include "../../Core/Resource.hpp"

namespace Framework {
	namespace Graphics {

		class Texture2D : public Texture, public Resource {
		public:
			Texture2D(std::string path, std::string resourceID);
			~Texture2D() = default;

			virtual void bind();
			virtual void unbind() const;

		};

	}
}

#endif
