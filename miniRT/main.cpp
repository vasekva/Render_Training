#include "Functions.hpp"
#include "Tests.hpp"

#include <iostream>

struct projectile
{
	projectile(const Vector4& pos, const Vector4& velocity)
	{
		this->position = createVector(pos.x, pos.y, pos.z);
		this->velocity = createVector(velocity.x, velocity.y, velocity.z);
	}

	Vector4* position;
	Vector4* velocity;
};

struct environment
{
	environment(const Vector4& gravity, const Vector4& wind)
	{
		this->gravity = createVector(gravity.x, gravity.y, gravity.z);
		this->wind = createVector(wind.x, wind.y, wind.z);
	}

	Vector4* gravity;
	Vector4* wind;
};

//TODO: leaks! replace to changing via a reference
projectile* tick(const environment& env, const projectile& proj)
{
	projectile* new_proj;

	Vector4* position = sum(*proj.position, *proj.velocity);
	Vector4* velocity = sum(*proj.velocity, *sum(*env.gravity, *env.wind));

	new_proj = new projectile(*position, *velocity);
	return new_proj;
}

void writePixel(canvas& cnv, int x, int y, Color *color)
{
	cnv(x, y) = Color(*color);
	//std::cout << cnv(x, y).r << std::endl;
}

int main()
{
	canvas* cnv = new canvas(5, 3);
	Color c1(0.5, 0, 0);
	Color c2(0, 0.5, 0);
	Color c3(-0.5, 0, 1);

	writePixel(*cnv, 0, 0, &c1);
	writePixel(*cnv, 2, 1, &c2);
	writePixel(*cnv, 4, 2, &c3);

	//cnv->createCanvas();

	canvas* new_c = new canvas(10, 2);

	Color c(1, 0.8, 0.6);
	for (int y = 0; y < 2; y++)
	{
		for (int x = 0; x < 10; x++)
		{
			writePixel(*new_c, x, y, &c);
		}
	}
	new_c->createCanvas();

	
	const Vector4* start = createPoint(0, 1, 0);

	const Vector4* velocity = (*normalize(*createVector(1, 1.8, 0))) * 11.25;

	projectile *proj = new projectile(*start, *velocity);
	environment* env = new environment(*createVector(0, -0.1, 0), *createVector(-0.01, 0, 0));

	canvas* print = new canvas(900, 550);

	Color red(1, 0, 0);
	while (proj->position->y >= 0)
	{
		float x = proj->position->x;
		float y = proj->position->y;
		writePixel(*print, x, y, &red);
		proj = (tick(*env, *proj));
	}
	print->createCanvas();
}

//TODO: make filling of the COlor's array with zero colors values and change them when try assign