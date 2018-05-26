#include "VertexFormat.h"

namespace Framework {
	namespace Graphics {

		VertexFormat::VertexFormat(unsigned int attribIndex, unsigned char numComponents, unsigned int type, bool normalized) :
			mAttribIndex(attribIndex),
			mNumComponents(numComponents),
			mType(type),
			mNormalized(normalized)
		{ }

		VertexFormat::VertexFormat(const VertexFormat& format) :
			mAttribIndex(format.mAttribIndex),
			mNumComponents(format.mNumComponents),
			mType(format.mType),
			mNormalized(format.mNormalized)
		{ }

	}
}