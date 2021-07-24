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

double Vec2d::operator*(Vec2d rhs) const {
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

Vec2d Vec2d::unit() const {
    if(isNull())
        return Vec2d(0, 0);
    else
        return *this / norm();
}

double Vec2d::norm() const {
    return std::hypot(x, y);
}

Vec2d Vec2d::normal() const {
    return Vec2d(y, -x);
}

Vec2d& Vec2d::reflect(Vec2d mirrorNormalUnit) 
{
    *this = reflected(mirrorNormalUnit);
    return *this;
}

Vec2d Vec2d::reflected(Vec2d mirrorNormalUnit) const
{
    return *this - 2.0 * (*this * mirrorNormalUnit) * mirrorNormalUnit;
}

bool Vec2d::isNull() const {
    return x == 0 && y == 0;
}

Vec2d operator*(double rhs, Vec2d lhs) 
{
    return lhs * rhs;
}
