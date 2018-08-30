#include "VertexFormat.h"

namespace GF {
	namespace Graphics {

		VertexFormat::VertexFormat(unsigned attribIndex, unsigned char numComponents, unsigned type, bool normalized) :
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