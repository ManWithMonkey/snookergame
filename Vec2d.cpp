#include "Vec2d.h"

Vec2d::Vec2d():
    x(0), y(0)
{
}

Vec2d::Vec2d(double x, double y) :
    x(x), y(y)
{    
}

Vec2d Vec2d::operator-() const
{
    return Vec2d(-x, -y);
}

Vec2d Vec2d::operator-(Vec2d rhs) const {
    return Vec2d(x - rhs.x, y - rhs.y);
}

Vec2d Vec2d::operator+(Vec2d rhs) const {
    return Vec2d(x + rhs.x, y + rhs.y);
}

Vec2d Vec2d::operator*(double f) const {
    return Vec2d(x * f, y * f);
}

Vec2d Vec2d::operator/(double f) const {
    return Vec2d(x / f, y / f);
}

double Vec2d::operator*(Vec2d rhs) {
    return x * rhs.x + y * rhs.y;
}

Vec2d& Vec2d::operator+=(Vec2d rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
}

Vec2d& Vec2d::operator-=(Vec2d rhs) {
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

Vec2d& Vec2d::operator*=(double rhs) {
    x *= rhs;
    y *= rhs;
    return *this;
}

Vec2d Vec2d::unit() {
    if(isNull())
        return Vec2d(0, 0);
    else
        return *this / norm();
}

double Vec2d::norm() {
    return std::hypot(x, y);
}

Vec2d Vec2d::normal() {
    return Vec2d(y, -x);
}

bool Vec2d::isNull() {
    return x == 0 && y == 0;
}
