#include <math.h>

struct Vec2d{
    double x, y;

    Vec2d();
    Vec2d(double x, double y);

    Vec2d operator-() const;

    Vec2d operator-(Vec2d rhs) const;
    Vec2d operator+(Vec2d rhs) const;
    Vec2d operator*(double f) const;
    Vec2d operator/(double f) const;

    double operator*(Vec2d rhs); // dot product

    Vec2d& operator+=(Vec2d rhs);
    Vec2d& operator-=(Vec2d rhs);

    Vec2d& operator*=(double rhs);

    Vec2d unit();
    double norm();
    Vec2d normal();

    bool isNull();
};