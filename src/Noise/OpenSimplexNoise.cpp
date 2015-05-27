#include "OpenSimplexNoise.hpp"

namespace swift
{
	constexpr std::array<char, 16> OpenSimplexNoise::gradients2D;
	constexpr std::array<char, 72> OpenSimplexNoise::gradients3D;
	constexpr std::array<char, 256> OpenSimplexNoise::gradients4D;

	OpenSimplexNoise::OpenSimplexNoise(unsigned long int seed)
	{
		std::array<int, 256> source;

		for(int i = 0; i < 256; i++)
			source[i] = i;

		// magic
		seed *= 6364136223846793005l;
		seed += 1442695040888963407l;
		seed *= 6364136223846793005l;
		seed += 1442695040888963407l;
		seed *= 6364136223846793005l;
		seed += 1442695040888963407l;

		for(int i = 255; i >= 0; i--)
		{
			seed *= 6364136223846793005l;
			seed += 1442695040888963407l;
			int r = (seed + 31) % (i + 1);

			if(r < 0)
				r += i + 1;

			perm[i] = source[r];
			permGradIndex3D[i] = (perm[i] % (gradients3D.size() / 3)) * 3.f;
			source[r] = source[i];
		}
	}
	
	double OpenSimplexNoise::evaluate(double x, double y)
	{
		// place coordinates onto grid
		double stretchOffset = (x + y) * STRETCH_2D;
		double xs = x + stretchOffset;
		double ys = y + stretchOffset;
		
		// get grid coordinates of rhombus super-cell origin
		int xsb = std::floor(xs);
		int ysb = std::floor(ys);
		
		// skew out to get actual coordinates of rhombus origin
		double squishOffset = (xsb + ysb) * SQUISH_2D;
		double xb = xsb + squishOffset;
		double yb = ysb + squishOffset;
		
		// compute grid coordinates relative to rhombus origin
		double xins = xs - xsb;
		double yins = ys - ysb;
		
		// sum together to get a value that determines which region we're in
		double inSum = xins + yins;
		
		// positions relative to origin point
		double dx0 = x - xb;
		double dy0 = y - yb;
		
		// vars to use in next block
		double dx_ext;
		double dy_ext;
		int xsv_ext;
		int ysv_ext;
		
		double value = 0;
		
		// Contribution (1, 0)
		double dx1 = dx0 - 1 - SQUISH_2D;
		double dy1 = dy0 - 0 - SQUISH_2D;
		double attn1 = 2 - dx1 * dx1 - dy1 * dy1;
		
		if(attn1 > 0)
		{
			attn1 *= attn1;
			value += attn1 * attn1 * extrapolate(xsb + 1, ysb + 0, dx1, dy1);
		}
		
		// Contribution (0, 1)
		double dx2 = dx0 - 0 - SQUISH_2D;
		double dy2 = dy0 - 1 - SQUISH_2D;
		
		double attn2 = 2 - dx2 * dx2 - dy2 * dy2;
		
		if(attn2 > 0)
		{
			attn2 *= attn2;
			value += attn2 * attn2 * extrapolate(xsb + 0, ysb + 1, dx2, dy2);
		}
		
		if(inSum <= 1)	// we're inside the triangle (2-Simplex) at (0, 0)
		{
			double zins = 1 - inSum;
			
			if(zins > xins || zins > yins)	// (0, 0) is one of the closest two triangular vertices
			{
				if(xins > yins)
				{
					xsv_ext = xsb + 1;
					ysv_ext = ysb - 1;
					dx_ext = dx0 - 1;
					dy_ext = dy0 + 1;
				}
				else
				{
					xsv_ext = xsb - 1;
					ysv_ext = ysb + 1;
					dx_ext = dx0 + 1;
					dy_ext = dy0 - 1;
				}
			}
			else	// (1, 0) and (0, 1) are the closest two vertices
			{
				xsv_ext = xsb + 1;
				ysv_ext = ysb + 1;
				dx_ext = dx0 - 1 - 2 * SQUISH_2D;
				dy_ext = dy0 - 1 - 2 * SQUISH_2D;
			}
		}
		else	// we're inside the triangle (2-Simplex) at (1, 1)
		{
			double zins = 2 - inSum;
			if(zins < xins || zins < yins)	// (0, 0) is one of the closest two triangular vertices
			{
				if(xins > yins)
				{
					xsv_ext = xsb + 2;
					ysv_ext = ysb + 0;
					dx_ext = dx0 - 2 - 2 * SQUISH_2D;
					dy_ext = dy0 + 0 - 2 * SQUISH_2D;
				}
				else
				{
					xsv_ext = xsb + 0;
					ysv_ext = ysb + 2;
					dx_ext = dx0 + 0 - 2 * SQUISH_2D;
					dy_ext = dy0 - 2 - 2 * SQUISH_2D;
				}
			}
			else	// (1, 0) and (0, 1) are the closest two vertices
			{
				dx_ext = dx0;
				dy_ext = dy0;
				xsv_ext = xsb;
				ysv_ext = ysb;
			}
			
			xsb += 1;
			ysb += 1;
			dx0 = dx0 - 1 - 2 * SQUISH_2D;
			dy0 = dy0 - 1 - 2 * SQUISH_2D;
		}
		
		// Contribution (0, 0) or (1, 1)
		double attn0 = 2 - dx0 * dx0 - dy0 * dy0;
		
		if(attn0 > 0)
		{
			attn0 *= attn0;
			value += attn0 * attn0 * extrapolate(xsb, ysb, dx0, dy0);
		}
		
		// Extra vertex
		double attn_ext = 2 - dx_ext * dx_ext - dy_ext * dy_ext;
		
		if(attn_ext > 0)
		{
			attn_ext *= attn_ext;
			value += attn_ext * attn_ext * extrapolate(xsv_ext, ysv_ext, dx_ext, dy_ext);
		}
		
		return value / NORM_2D;
	}
	
//	double OpenSimplexNoise::evaluate(double x, double y, double z)
//	{
//		
//	}
//	
//	double OpenSimplexNoise::evaluate(double x, double y, double z, double t)
//	{
//		
//	}
	
	double OpenSimplexNoise::extrapolate(int xsb, int ysb, double dx, double dy)
	{
		int index = perm[(perm[xsb & 0xFF] + ysb) & 0xFF] & 0x0E;
		return gradients2D[index] * dx + gradients2D[index + 1] * dy;
	}
	
//	double OpenSimplexNoise::extrapolate(int xsb, int ysb, int zsb, double dx, double dy, double dz)
//	{
//		
//	}
//	
//	double OpenSimplexNoise::extrapolate(int xsb, int ysb, int zsb, int tsb, double dx, double dy, double dz, double dt)
//	{
//		
//	}
}
