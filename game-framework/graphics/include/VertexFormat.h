#ifndef GRAPHICS_VERTEXFORMAT_H
#define GRAPHICS_VERTEXFORMAT_H
#pragma once

#include <GL/glew.h>

namespace GF {
	namespace Graphics {

		class VertexFormat {
		private:
			unsigned char mNumComponents = -1;

			unsigned
				mAttribIndex = 0,
				mType = GL_FLOAT;

			bool mNormalized = false;

		public:
			VertexFormat(unsigned attribIndex, unsigned char numComponents, unsigned type, bool normalized = false);
			VertexFormat(const VertexFormat& format);
			~VertexFormat() = default;

			unsigned char getNumComponents() const { return mNumComponents; }
			unsigned getAttribIndex() const { return mAttribIndex; }
			unsigned getType() const { return mType; }
			bool isNormalized() const { return mNormalized; }

		};

	}
}

#endif
