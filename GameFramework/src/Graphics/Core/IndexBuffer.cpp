#include "IndexBuffer.h"

namespace Framework {
	namespace Graphics {
		
		IndexBuffer::IndexBuffer(unsigned int usage, const std::vector<unsigned int>& data, std::string resourceID) :
			Resource(resourceID),
			mUsage(usage),
			mCount(data.size())
		{
			glGenBuffers(1, &mHandle);
			bind();
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(data[0]) * data.size(), data.data(), usage);
			unbind();
		}

		IndexBuffer::~IndexBuffer() {
			glDeleteBuffers(1, &mHandle);
		}

		void IndexBuffer::updateData(const std::vector<unsigned int>& newData) {
			mCount = newData.size();

			bind();

			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(newData[0]) * newData.size(), newData.data());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(newData[0]) * newData.size(), newData.data(), mUsage);
		}
	}
}