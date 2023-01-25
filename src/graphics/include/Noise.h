#ifndef NOISE_H
#define NOISE_H
#pragma once

#include <vector>
#include <glm/vec2.hpp>
#include <Maths.hpp>

namespace GF {
	namespace Maths {

		class Noise {
		private:
			static int mSeed;
			static unsigned permutation[256];
			static std::vector<unsigned> p;			
			static bool permutationsInitialised;

		public:
			static double perlin(double x, double z);
			static double multiFractalBillowed(double x, double z, double lacunarity, double gain, double octaves);
			static double multiFractalRidged(double x, double z, double lacunarity, double gain, double octaves);

			static double grad(int hash, double x, double y, double z);
			static double fade(double t);
			static double octavePerlin(double x, double z, int octaves, double persistence);
			static void initPermutations();

		};

	}
}

#endif
