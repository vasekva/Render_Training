#pragma once

#include <cmath>
#include <vector>

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

struct Vector4;

const float EPSILON = 0.00001f;

bool equal(float a, float b);
// TODO: refactor to both const
Vector4* sum(Vector4& a, const Vector4& b);
// TODO: refactor to both const
Vector4* subtruct(Vector4& a, const Vector4& b);
Vector4* multiply(const Vector4& a, const Vector4& b);
Vector4* devide(const Vector4& a, const Vector4& b);

float clampFloat(float min, float max, float val);

float magnitude(const Vector4& a);
float dotProduct(const Vector4& a, const Vector4& b);
Vector4* crossProduct(const Vector4& a, const Vector4& b);

Vector4* normalize(const Vector4& a);

Vector4* createVector(float x, float y, float z);
Vector4* createPoint(float x, float y, float z);

struct Vector4
{
	Vector4()
	{
		this->x = 0.;
		this->y = 0.;
		this->z = 0.;
		this->w = 0.;
	}

	//Vector4(const Vector4&) = delete;

	Vector4(float x, float y, float z, float w)
	{
		this->x = x;
		this->y = y;
		this->z = z;
		this->w = w;
	}

	~Vector4() {};

	Vector4* operator+(const Vector4& b)
	{
		Vector4* vec = new Vector4(0., 0., 0., 0.);
		vec->x = this->x + b.x;
		vec->y = this->y + b.y;
		vec->z = this->z + b.z;
		vec->w = this->w + b.w;
		return vec;
	}

	Vector4* operator*(float factor)
	{
		Vector4* vec = new Vector4(0., 0., 0., 0.);
		vec->x = this->x * factor;
		vec->y = this->y * factor;
		vec->z = this->z * factor;
		vec->w = this->w;
		return vec;
	}

	Vector4* operator/(float factor)
	{
		Vector4* vec = new Vector4(0., 0., 0., 0.);
		vec->x = this->x / factor;
		vec->y = this->y / factor;
		vec->z = this->z / factor;
		vec->w = this->w;
		return vec;
	}

	Vector4* operator-(const Vector4& b)
	{
		Vector4* vec = new Vector4(0., 0., 0., 0.);
		vec->x = this->x - b.x;
		vec->y = this->y - b.y;
		vec->z = this->z - b.z;
		vec->w = this->w - b.w;
		return vec;
	}

	float x;
	float y;
	float z;
	float w;
};

struct Color
{
	Color()
	{
		r = 0;
		g = 0;
		b = 0;
		//std::cout << "WOW" << std::endl;
	}

	Color(float r, float g, float b)
	{
		this->r = std::round(clampFloat(0, 255, 255 * r));
		this->g = std::round(clampFloat(0, 255, 255 * g));
		this->b = std::round(clampFloat(0, 255, 255 * b));
	}

	Color& operator=(Color* clr) { return *clr; }

	float r;
	float g;
	float b;
};

struct canvas
{
	canvas() = delete;
	canvas(const canvas&) = delete;

	canvas(int width, int height)
	{
		canvasValues = new Color[width * height];
		this->width = width;
		this->height = height;
	}

	// TODO: leaks! needs to clean Color correctly!
	~canvas() { delete[] canvasValues; }

	int GetWidth() const { return width; }
	int GetHeight() const { return height; }

	Color& operator() (int x, int y)
	{
		// TODO: check boundaries
		return canvasValues[x + this->width * y];
	}

	// TODO: create canvas by name
	void createCanvas()
	{
		outfile.open("canvas.ppm");
		outfile << "P3\n" <<
			width << " " << height << "\n" <<
			"255" << std::endl;

		std::string str;
		std::string line;

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				line += std::to_string((int)canvasValues[x + this->width * y].r);
				line += " ";
				line += std::to_string((int)canvasValues[x + this->width * y].g);
				line += " ";
				line += std::to_string((int)canvasValues[x + this->width * y].b);

				if (line.length() > 70)
				{
					line[line.find_last_of(" ")] = '\n';
					str += line;
					line.clear();
				}

				if (x + 1 == width)
					line += '\n';
				else
					line += ' ';

			}
			str += line;
			line.clear();
		}
		outfile << str;
		outfile.close();
	}

private:
	int width;
	int height;

	Color* canvasValues;
	std::ofstream outfile;
};