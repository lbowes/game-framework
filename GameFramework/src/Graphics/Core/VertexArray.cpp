#include "VertexArray.h"
#include <iostream>

namespace Framework {
	namespace Graphics {

		VertexArray::VertexArray(unsigned int geometryType) :
			mGeometryType(geometryType)
		{
			glGenVertexArrays(1, &mHandle);
		}

		VertexArray::~VertexArray() {
			glDeleteVertexArrays(1, &mHandle);
		}

		void VertexArray::attachBuffer(VertexBuffer* newConnectedBuffer) {
			mAttachedBuffers.push_back(newConnectedBuffer);
			refreshVAOState();
		}

		void VertexArray::attachIndexBuffer(IndexBuffer* indexBuffer) {
			mAttachedIndexBuffer = indexBuffer;
			refreshVAOState();
		}

		void VertexArray::refreshVAOState() {
			bind();

			VertexFormat* format = nullptr;
			for (VertexBuffer* b : mAttachedBuffers) {
				format = b->getFormat();
				
				b->bind();
				glVertexAttribPointer(format->getAttribIndex(), format->getNumComponents(), format->getType(), format->isNormalized(), 0, (GLvoid*)0);
				glEnableVertexAttribArray(format->getAttribIndex());
			}

			if(mAttachedIndexBuffer)
				mAttachedIndexBuffer->bind();

			unbind();
		}

		void VertexArray::draw() const {
			bind();

			//If someone forgets to attach the index buffer, then don't try to draw anything
			if(mAttachedIndexBuffer)
				glDrawElements(mGeometryType, mAttachedIndexBuffer->getCount(), GL_UNSIGNED_INT, NULL);
		}

	}
}