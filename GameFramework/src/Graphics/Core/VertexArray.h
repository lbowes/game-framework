#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#pragma once

#include "VertexBuffer.h"
#include "IndexBuffer.h"

namespace Framework {
	namespace Graphics {

		class VertexArray {
		private:
			unsigned int mHandle = 0;
			
			//The vertex array should *NOT* own the buffers - it simply ties them together.
			//This way, VBOs and index buffers can be shared around to save memory on objects that use duplicate buffers.
			IndexBuffer* mAttachedIndexBuffer = nullptr;
			std::vector<VertexBuffer*> mAttachedBuffers;
			unsigned int mGeometryType = GL_TRIANGLES;

		public:
			VertexArray(unsigned int geometryType);
			~VertexArray();

			//The buffer attached using this function is managed elsewhere. The VAO does not need to care about how it is managed.
			//As long as it will outlive the buffer then the VAO does not need to worry about the management of the buffer.
			void attachBuffer(VertexBuffer* buffer);
			void attachIndexBuffer(IndexBuffer* indexBuffer);

			//This makes the glDrawElements() call
			void draw() const;

			inline void bind() const { glBindVertexArray(mHandle); }
			inline void unbind() const { glBindVertexArray(0); }

		private:
			//Each time a buffer (or index buffer) is added, the state stored by the VAO has to be updated to include this new buffer.
			void refreshVAOState();

		};

	}
}

#endif
