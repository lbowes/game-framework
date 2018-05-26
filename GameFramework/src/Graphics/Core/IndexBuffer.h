#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H
#pragma once

#include <GLEW/glew.h>
#include <vector>

#include "../../Core/Resource.hpp"

namespace Framework {
	namespace Graphics {

		class IndexBuffer : public Resource {
		private:
			unsigned int
				mHandle = 0,
				mUsage = 0,
				mCount = 0;

		public:
			IndexBuffer() = default;
			IndexBuffer(unsigned int usage, const std::vector<unsigned int>& data, std::string resourceID);
			~IndexBuffer();

			inline void bind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mHandle); }
			inline void unbind() const { glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0); }
			inline unsigned int getCount() const { return mCount; }

			void updateData(const std::vector<unsigned int>& newData);

		};

	}
}

#endif
