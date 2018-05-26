#include "VertexBuffer.h"
#include <iostream>

namespace Framework {
	namespace Graphics {

		VertexBuffer::VertexBuffer(unsigned int usage, const VertexFormat& format, const std::vector<float>& data, std::string resourceID) :
			Resource(resourceID),
			mUsage(usage),
			mFormat(std::make_unique<VertexFormat>(format))
		{
			glGenBuffers(1, &mHandle);
			bind();
			glBufferData(GL_ARRAY_BUFFER, sizeof(data[0]) * data.size(), data.data(), usage);
			glVertexAttribPointer(format.getAttribIndex(), format.getNumComponents(), format.getType(), format.isNormalized(), 0, 0);
			glEnableVertexAttribArray(format.getAttribIndex());
			unbind();
		}

		VertexBuffer::~VertexBuffer() {
			glDeleteBuffers(1, &mHandle);
		}

		void VertexBuffer::updateData(const std::vector<float>& newData) const {
			bind();

			//TODO: This should be glBufferData for setting the data for the first time, and glBufferSubData for updating it
			//If the newData size is greater than the old data size, then glBufferData must be used. If the size starts of as being
			//0, then no sub data can be updated!

			//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(newData[0]) * newData.size(), newData.data());
			glBufferData(GL_ARRAY_BUFFER, sizeof(newData[0]) * newData.size(), newData.data(), mUsage);
		}

	}
}