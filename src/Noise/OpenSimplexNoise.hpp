#ifndef OPENSIMPLEXNOISE_HPP
#define OPENSIMPLEXNOISE_HPP

#include <cmath>
#include <array>

#include "../Math/Math.hpp"

namespace swift
{
	class OpenSimplexNoise
	{
		public:
			OpenSimplexNoise(unsigned long int seed);

			double evaluate(double x, double y);
			double evaluate(double x, double y, double z);
			double evaluate(double x, double y, double z, double t);

		private:
			double extrapolate(int xsb, int ysb, double dx, double dy);
			double extrapolate(int xsb, int ysb, int zsb, double dx, double dy, double dz);
			double extrapolate(int xsb, int ysb, int zsb, int tsb, double dx, double dy, double dz, double dt);

			std::array<int, 256> perm;
			std::array<int, 256> permGradIndex3D;

			static constexpr double STRETCH_2D = (1.f / std::sqrt(2.f + 1.f) - 1.f) / 2.f;
			static constexpr double SQUISH_2D = (std::sqrt(2.f + 1.f) - 1.f) / 2.f;
			static constexpr double STRETCH_3D = (1.f / std::sqrt(3.f + 1.f) - 1.f) / 3.f;
			static constexpr double SQUISH_3D = (std::sqrt(3.f + 1.f) - 1.f) / 3.f;
			static constexpr double STRETCH_4D = (1.f / std::sqrt(4.f + 1.f) - 1.f) / 4.f;
			static constexpr double SQUISH_4D = (std::sqrt(4.f + 1.f) - 1.f) / 4.f;

			static constexpr double NORM_2D = 47;
			static constexpr double NORM_3D = 103;
			static constexpr double NORM_4D = 30;

			// Gradients for 2D. They approximate the directions to the
			// vertices of an octagon from the center.
			static constexpr std::array<char, 16> gradients2D =
			{
				5, 2, 2, 5,
				-5, 2, -2, 5,
				5, -2, 2, -5,
				-5, -2, -2, -5
			};

			// Gradients for 3D. They approximate the directions to the
			// vertices of a rhombicuboctahedron from the center, skewed so
			// that the triangular and square facets can be inscribed inside
			// circles of the same radius.
			static constexpr std::array<char, 72> gradients3D =
			{
				-11,  4,  4,     -4,  11,  4,    -4,  4,  11,
				11,  4,  4,      4,  11,  4,     4,  4,  11,
				-11, -4,  4,     -4, -11,  4,    -4, -4,  11,
				11, -4,  4,      4, -11,  4,     4, -4,  11,
				-11,  4, -4,     -4,  11, -4,    -4,  4, -11,
				11,  4, -4,      4,  11, -4,     4,  4, -11,
				-11, -4, -4,     -4, -11, -4,    -4, -4, -11,
				11, -4, -4,      4, -11, -4,     4, -4, -11,
			};

			// Gradients for 4D. They approximate the directions to the
			// vertices of a disprismatotesseractihexadecachoron from the center,
			// skewed so that the tetrahedral and cubic facets can be inscribed inside
			// spheres of the same radius.
			static constexpr std::array<char, 256> gradients4D =
			{
				3,  1,  1,  1,      1,  3,  1,  1,      1,  1,  3,  1,      1,  1,  1,  3,
				-3,  1,  1,  1,     -1,  3,  1,  1,     -1,  1,  3,  1,     -1,  1,  1,  3,
				3, -1,  1,  1,      1, -3,  1,  1,      1, -1,  3,  1,      1, -1,  1,  3,
				-3, -1,  1,  1,     -1, -3,  1,  1,     -1, -1,  3,  1,     -1, -1,  1,  3,
				3,  1, -1,  1,      1,  3, -1,  1,      1,  1, -3,  1,      1,  1, -1,  3,
				-3,  1, -1,  1,     -1,  3, -1,  1,     -1,  1, -3,  1,     -1,  1, -1,  3,
				3, -1, -1,  1,      1, -3, -1,  1,      1, -1, -3,  1,      1, -1, -1,  3,
				-3, -1, -1,  1,     -1, -3, -1,  1,     -1, -1, -3,  1,     -1, -1, -1,  3,
				3,  1,  1, -1,      1,  3,  1, -1,      1,  1,  3, -1,      1,  1,  1, -3,
				-3,  1,  1, -1,     -1,  3,  1, -1,     -1,  1,  3, -1,     -1,  1,  1, -3,
				3, -1,  1, -1,      1, -3,  1, -1,      1, -1,  3, -1,      1, -1,  1, -3,
				-3, -1,  1, -1,     -1, -3,  1, -1,     -1, -1,  3, -1,     -1, -1,  1, -3,
				3,  1, -1, -1,      1,  3, -1, -1,      1,  1, -3, -1,      1,  1, -1, -3,
				-3,  1, -1, -1,     -1,  3, -1, -1,     -1,  1, -3, -1,     -1,  1, -1, -3,
				3, -1, -1, -1,      1, -3, -1, -1,      1, -1, -3, -1,      1, -1, -1, -3,
				-3, -1, -1, -1,     -1, -3, -1, -1,     -1, -1, -3, -1,     -1, -1, -1, -3,
			};
	};
}

#endif // OPENSIMPLEXNOISE_HPP
