#pragma once
class PerlinNoise
{
private:
	int p[512];
public:
	PerlinNoise();
	virtual~PerlinNoise();
	double perlinNoise2D(double x, double y);
	static double grad(int hash, double x, double y);
	static double fade(double t);
	static double lerp(double a, double b, double x);
};

