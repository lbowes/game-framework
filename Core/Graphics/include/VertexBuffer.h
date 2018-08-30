#ifndef GRAPHICS_VERTEXBUFFER_H
#define GRAPHICS_VERTEXBUFFER_H
#pragma once

#include <vector>
#include <memory>

#include "VertexFormat.h"
#include "Resource.hpp"

namespace GF {
	namespace Graphics {

		class VertexBuffer : public Resource {
		private:
			unsigned 
				mHandle = 0,
				mUsage = 0;
			
			std::unique_ptr<VertexFormat> mFormat;

		public:
			VertexBuffer() = default;
			VertexBuffer(unsigned usage, const VertexFormat& format, const std::vector<float>& data, const std::string& resID);
			~VertexBuffer();

			inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, mHandle); }
			inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
			inline VertexFormat* getFormat() const { return mFormat.get(); }

			void updateData(const std::vector<float>& newData) const;

		};

	}
}

#endif
