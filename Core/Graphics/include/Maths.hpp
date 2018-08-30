#ifndef MATHS_HPP
#define MATHS_HPP
#pragma once

#include <math.h>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>

namespace GF {
	namespace Maths {

		static float barycentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos) {
			float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
			float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
			float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
			float l3 = 1.0f - l1 - l2;

			return l1 * p1.y + l2 * p2.y + l3 * p3.y;
		}

		static double lerp(double t, double a, double b) {
			return a + t * (b - a);
		}

	}
}

#endif
