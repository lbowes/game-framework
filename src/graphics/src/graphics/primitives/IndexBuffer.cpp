#include "IndexBuffer.h"

namespace GF {
	namespace Graphics {
		
		IndexBuffer::IndexBuffer(unsigned usage, const std::vector<unsigned>& data, const std::string& resID) :
			Resource(resID),
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

		void IndexBuffer::updateData(const std::vector<unsigned>& newData) {
			mCount = newData.size();

			bind();

			//glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(newData[0]) * newData.size(), newData.data());
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(newData[0]) * newData.size(), newData.data(), mUsage);
		}
	}
}