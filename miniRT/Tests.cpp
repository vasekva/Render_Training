#include "Functions.hpp"


bool isPoint(const Vector4& vec)
{
	return vec.w == 1 ? 1 : 0;
}

bool isVector(const Vector4& vec)
{
	return vec.w == 0 ? 1 : 0;
}