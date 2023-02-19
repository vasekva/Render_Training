#include "Functions.hpp"

bool equal(float a, float b)
{
	if ((abs(a - b)) < EPSILON)
		return true;
	else
		return false;
}

// TODO: refactor to both const
Vector4* sum(Vector4& a, const Vector4& b)
{
	return a + b;
}

// TODO: refactor to both const
Vector4* subtruct(Vector4& a, const Vector4& b)
{
	return a - b;
}

Vector4* multiply(const Vector4& a, const Vector4& b)
{
	Vector4* newVec = new Vector4();
	newVec->x = a.x * b.x;
	newVec->y = a.y * b.y;
	newVec->z = a.z * b.z;
	newVec->w = a.w * b.w;

	return newVec;
}

float magnitude(const Vector4& a)
{
	return std::sqrt(std::powf(a.x, 2) + std::powf(a.y, 2) + std::powf(a.z, 2) + std::powf(a.w, 2));
}

Vector4* devide(const Vector4& a, const Vector4& b)
{
	//TODO: check for zero

	Vector4* newVec = new Vector4();
	newVec->x = a.x / b.x;
	newVec->y = a.y / b.y;
	newVec->z = a.z / b.z;
	newVec->w = a.w / b.w;

	return newVec;
}

Vector4* normalize(const Vector4& a)
{
	Vector4* normalizedV = new Vector4();
	normalizedV->x = a.x / magnitude(a);
	normalizedV->y = a.y / magnitude(a);
	normalizedV->z = a.z / magnitude(a);
	normalizedV->w = a.w / magnitude(a);

	return normalizedV;
}

float dotProduct(const Vector4& a, const Vector4& b)
{
	return (a.x * b.x) + (a.y * b.y) + (a.z * b.z) + (a.w * b.w);
}

Vector4* createVector(float x, float y, float z)
{
	return new Vector4(x, y, z, 0.);
}

Vector4* createPoint(float x, float y, float z)
{
	return new Vector4(x, y, z, 1.);
}

Vector4* crossProduct(const Vector4& a, const Vector4& b)
{
	float x = a.y * b.z - a.z * b.y;
	float y = a.z * b.x - a.x * b.z;
	float z = a.x * b.y - a.y * b.x;

	return (createVector(x, y, z));
}

float clampFloat(float min, float max, float val)
{
	float clampedValue = val;

	if (val < min)
		clampedValue = min;
	else if (val > max)
		clampedValue = max;
	return clampedValue;
}
