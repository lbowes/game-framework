#ifndef GRAPHICS_INDEXBUFFER_H
#define GRAPHICS_INDEXBUFFER_H
#pragma once

#include <GL/glew.h>
#include <vector>

#include "Resource.hpp"

namespace GF {
	namespace Graphics {

		class IndexBuffer : public Resource {
		private:
			unsigned
				mHandle = 0,
				mUsage = 0;

			size_t mCount = 0;

		public:
			IndexBuffer() = default;
			IndexBuffer(unsigned usage, const std::vector<unsigned>& data, const std::string& resID);
			~IndexBuffer();

			inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle); }
			inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
			inline size_t getCount() const { return mCount; }

			void updateData(const std::vector<unsigned>& newData);

		};

	}
}

#endif
