#include "Vector3.h"
#include "math.h"

Vector3::Vector3() {}

Vector3::Vector3(double aX, double aY, double aZ) :
	x(aX),
	y(aY),
	z(aZ) {
}

Vector3::Vector3(const Vector3& a) :
	x(a.x),
	y(a.y),
	z(a.z) {
}

void Vector3::set(double aX, double aY, double aZ) {
	x = aX;
	y = aY;
	z = aZ;
}

void Vector3::operator+=(const Vector3& a) {
	x += a.x;
	y += a.y;
	z += a.z;
}

void Vector3::operator-=(const Vector3& a) {
	x -= a.x;
	y -= a.y;
	z -= a.z;
}

void Vector3::operator=(const Vector3& a) {
	x = a.x;
	y = a.y;
	z = a.z;
}

void Vector3::setAdd(const Vector3& a, const Vector3& b) {
	x = a.x + b.x;
	y = a.y + b.y;
	z = a.z + b.z;
}

void Vector3::setSub(const Vector3& a, const Vector3& b) {
	x = a.x - b.x;
	y = a.y - b.y;
	z = a.z - b.z;
}

void Vector3::cross(const Vector3& a, const Vector3& b) {
	x = a.y * b.z - b.y * a.z;
	y = a.z * b.x - b.z * a.x;
	z = a.x * b.y - b.x * a.y;
}

void Vector3::normalize() {
	int r = x * x + y * y + z * z;
	x = x / sqrt(r);
	y = y / sqrt(r);
	z = z / sqrt(r);
}

double Vector3::dot(const Vector3& a) {
	return x * a.x + y * a.y + z * a.z;
}
