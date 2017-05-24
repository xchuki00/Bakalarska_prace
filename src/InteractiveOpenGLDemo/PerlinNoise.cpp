#include "PerlinNoise.h"
#include "includes.h"
static int permutation[256] = { 151,160,137,91,90,15,					// Hash lookup table as defined by Ken Perlin.  This is a randomly
131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,	// arranged array of all numbers from 0-255 inclusive.
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


PerlinNoise::PerlinNoise()
{
	for (int i = 0; i < 512; i++) {
		this->p[i] = permutation[i % 256];
	}

}


PerlinNoise::~PerlinNoise()
{
}

double PerlinNoise::perlinNoise2D(double x, double y)
{
	int ix = (int)x & 255;
	int iy = (int)y & 255;
	x -= (int)x;
	y -= (int)y;
	double u = fade(x);
	double v = fade(y);
	int c00 = this->p[ix +     p[iy  ]];
	int c01 = this->p[ix +     p[iy+1]];
	int c10 = this->p[ix + 1 + p[iy  ]];
	int c11 = this->p[ix + 1 + p[iy+1]];
	float g00 = grad(c00, x, y);
	float g01 = grad(c01, x, y-1);
	float g10 = grad(c10, x-1, y);
	float g11 = grad(c11, x-1, y-1);

	return lerp(v,lerp(u,g00,g01),lerp(u,g10,g11));
}

double PerlinNoise::grad(int hash, double x, double y)
{
	int h = hash & 7;                      
	double u = h == 2 || h == 6 ? 0 : y;
	double 	v = h == 0 || h == 4 ? 0 : x;
	return (h <4 ? v : -v) + (h >5||h<3 ? u : -u);

}

double PerlinNoise::fade(double t)
{
	return t*t*t*(t*(t*6-15)+10);
}

double PerlinNoise::lerp(double a, double b, double x)
{
	return a+x*(b-a);
}

