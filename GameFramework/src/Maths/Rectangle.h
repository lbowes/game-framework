#ifndef RECTANGLE_H
#define RECTANGLE_H
#pragma once

#include <glm\glm\vec2.hpp>

namespace Framework {
	namespace Maths {

		class Rectangle {
		private:
			glm::vec2 mPosition;
			float mWidth, mHeight;

		public:
			Rectangle(glm::vec2 position, float width, float height);
			Rectangle(const Rectangle& r);

			bool contains(glm::vec2 point);
			bool overlaps(Rectangle& r);

		};

	}
}

#endif
