#include "Rectangle.h"

namespace Framework {
	namespace Maths {

		Rectangle::Rectangle(glm::vec2 position, float width, float height) :
			mPosition(position), mWidth(width), mHeight(height)
		{}

		Rectangle::Rectangle(const Rectangle& r) :
			mPosition(r.mPosition), mWidth(r.mWidth), mHeight(r.mHeight)
		{}

		bool Rectangle::contains(glm::vec2 point) {
			return point.x > mPosition.x && point.y > mPosition.y && point.x < mWidth && point.y < mHeight;
		}

		bool Rectangle::overlaps(Rectangle& r) {
			return contains(r.mPosition) ||
				contains(glm::vec2(r.mPosition.x, r.mPosition.y + mHeight)) ||
				contains(glm::vec2(r.mPosition.x + r.mWidth, r.mPosition.y + r.mHeight)) ||
				contains(glm::vec2(r.mPosition.x + mWidth, r.mPosition.y));
		}

	}
}