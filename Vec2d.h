#ifndef __VEC2D_H__
#define __VEC2D_H__

#include <math.h>

struct Vec2d {
	double x, y;

	Vec2d();
	Vec2d(double x, double y);

	Vec2d operator-() const;

	Vec2d operator-(Vec2d rhs) const;
	Vec2d operator+(Vec2d rhs) const;
	Vec2d operator*(double f) const;
	Vec2d operator/(double f) const;

	double operator*(Vec2d rhs) const; // dot product

	Vec2d &operator+=(Vec2d rhs);
	Vec2d &operator-=(Vec2d rhs);

	Vec2d &operator*=(double rhs);

	Vec2d unit() const;
	double norm() const;
	Vec2d normal() const;

	Vec2d &reflect(Vec2d mirrorNormalUnit);
	Vec2d reflected(Vec2d mirrorNormalUnit) const;

	double angle() const;
	Vec2d &rotate(double angle);
	Vec2d rotated(double angle) const;

	bool isNull() const;
};

Vec2d operator*(double rhs, Vec2d lhs);

#endif // __VEC2D_H__