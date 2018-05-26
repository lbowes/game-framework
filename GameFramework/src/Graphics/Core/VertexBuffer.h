#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#pragma once

#include <vector>
#include <memory>

#include "VertexFormat.h"
#include "../../Core/Resource.hpp"

namespace Framework {
	namespace Graphics {

		class VertexBuffer : public Resource {
		private:
			unsigned int 
				mHandle = 0,
				mUsage = 0;
			
			std::unique_ptr<VertexFormat> mFormat;

		public:
			VertexBuffer() = default;
			VertexBuffer(unsigned int usage, const VertexFormat& format, const std::vector<float>& data, std::string resourceID);
			~VertexBuffer();

			inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, mHandle); }
			inline void unbind() const { glBindBuffer(GL_ARRAY_BUFFER, 0); }
			inline VertexFormat* getFormat() const { return mFormat.get(); }

			void updateData(const std::vector<float>& newData) const;

		};

	}
}

#endif
