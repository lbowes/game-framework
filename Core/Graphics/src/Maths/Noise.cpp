#include "Noise.h"

namespace GF {
	namespace Maths {

		std::vector<unsigned> Noise::p;
		bool Noise::permutationsInitialised = false;

		unsigned Noise::permutation[256] = { 151,160,137,91,90,15,			
			131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
			190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
			88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
			77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
			102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
			135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
			5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
			223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
			129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
			251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
			49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
			138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
		};

		void Noise::initPermutations() {
			p = std::vector<unsigned>(512);
			for (int x = 0; x < p.size(); x++) {
				p[x] = permutation[x % 256];
			}
		}

		double Noise::perlin(double x, double z) {		
			if (!permutationsInitialised)
				initPermutations();
			permutationsInitialised = true;
			
			int xi = static_cast<int>(floor(x)) & 255;	
			int zi = static_cast<int>(floor(z)) & 255;						
			
			double xf = x < 0 ? fabs(floor(x) - x) : x - floor(x);
			double zf = z < 0 ? fabs(floor(z) - z) : z - floor(z);

			double u = fade(xf);
			double w = fade(zf);

			int aaa, aba, aab, abb, baa, bba, bab, bbb;
			aaa = p[p[p[xi]] + zi];
			aba = p[p[p[xi] + 1] + zi];
			aab = p[p[p[xi]] + zi + 1];
			abb = p[p[p[xi] + 1] + zi + 1];
			baa = p[p[p[xi + 1]] + zi];
			bba = p[p[p[xi + 1] + 1] + zi];
			bab = p[p[p[xi + 1]] + zi + 1];
			bbb = p[p[p[xi + 1] + 1] + zi + 1];

			double x1, x2, y1, y2;
			x1 = lerp(u, 
				grad(aaa, xf, 0, zf),
				grad(baa, xf - 1, 0, zf));								
			x2 = lerp(u,
				grad(aba, xf, -1, zf),
				grad(bba, xf - 1, -1, zf));
			y1 = lerp(0, x1, x2);

			x1 = lerp(u,
				grad(aab, xf, 0, zf - 1),
				grad(bab, xf - 1, 0, zf - 1));
			x2 = lerp(u,
				grad(abb, xf, -1, zf - 1),
				grad(bbb, xf - 1, -1, zf - 1));
			y2 = lerp(0, x1, x2);

			return lerp(w, y1, y2);
		}

		double Noise::multiFractalBillowed(double x, double z, double lacunarity, double gain, double octaves) {
#if 0
			float sum = 1.0f - fabsf(perlin(x, z));
			float amp = 1.0f;

			for (int i = 0; i < octaves; i++) {
				x *= lacunarity;
				z *= lacunarity;

				amp *= gain;

				sum -= (1.0f - fabsf(perlin(x, z))) * amp;
			}

			return sum;
#else
			double 
				perlinResult = perlin(x, z),
				sum = perlinResult,
				amp = 1.0f;

			for (int i = 0; i < octaves; i++) {
				x *= lacunarity;
				z *= lacunarity;
				amp *= gain;

				perlinResult = perlin(x, z);

				if (perlinResult < -0.3f)
					sum += abs(perlinResult) * amp;
				else if (perlinResult > 0)
					sum += perlinResult * amp;
			}

			return sum;
#endif
		}

		double Noise::multiFractalRidged(double x, double z, double lacunarity, double gain, double octaves) {
			return -multiFractalBillowed(x, z, lacunarity, gain, octaves);
		}

		double Noise::fade(double t) {
			return t * t * t * (t * (t * 6 - 15) + 10);
		}

		double Noise::grad(int hash, double x, double y, double z) {
			int h = hash & 15;					
			double u = h < 8 ? x : y;			

			double v;							
												
			if (h < 4)								 
				v = y;
			else if (h == 12 || h == 14)
				v = x;
			else 												
				v = z;

			return ((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v);
		}

		double Noise::octavePerlin(double x, double z, int octaves, double persistence) {
			double total = 0;
			double frequency = 1;
			double amplitude = 1;
			double maxValue = 0;
			for (int i = 0; i<octaves; i++) {
				total += perlin(x * frequency, z * frequency) * amplitude;

				maxValue += amplitude;

				amplitude *= persistence;
				frequency *= 2;
			}

			return total / maxValue;
		}

	}
}