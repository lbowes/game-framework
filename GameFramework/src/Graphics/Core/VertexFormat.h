#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H
#pragma once

#include <GLEW/glew.h>

namespace Framework {
	namespace Graphics {

		class VertexFormat {
		private:
			unsigned char mNumComponents = -1;
			unsigned int
				mAttribIndex = 0,
				mType = GL_FLOAT;
			bool mNormalized = false;

		public:
			VertexFormat(unsigned int attribIndex, unsigned char numComponents, unsigned int type, bool normalized);
			VertexFormat(const VertexFormat& format);
			~VertexFormat() = default;

			inline unsigned char getNumComponents() const { return mNumComponents; }
			inline unsigned int getAttribIndex() const { return mAttribIndex; }
			inline unsigned int getType() const { return mType; }
			inline bool isNormalized() const { return mNormalized; }

		};

	}
}

#endif
