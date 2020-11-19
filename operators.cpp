#include "operators.h"

////////////////////
// Enhanced std:: //
////////////////////

// output vector of strings
std::ostream& operator<<(std::ostream& os, std::vector<std::string>& v)
{
	if (v.empty()) return os << "{ VECTOR_EMPTY }";

	auto iter = v.begin();
	auto iEnd = v.end() - 1;
	os << "{ ";
	while(iter != iEnd) os << *(iter++) << " ";

	return os << "}";
}

// basic linear search algorithms (STRING)
bool is_in(std::vector<std::string> names, std::string str)
{
	auto iter = names.begin(), iEnd = names.end();
	bool q = false;
	while (iter != iEnd) q |= (str == *(iter++));

	return q;
}

bool not_in(std::vector<std::string> names, std::string str)
{
	return !is_in(names, str);
}

////////////////////////////
// lib type extensions //
////////////////////////////

// Vector addition
Vector2 operator+(const Vector2& a, const Vector2& b)
{
	return Vector2{a.x + b.x, a.y + b.y};
}

Vector2 operator*(const float& c, const Vector2& x)
{
	return Vector2{c * x.x, c * x.y};
}

Vector2 operator*(const Vector2& x, const float& c)
{
	return c * x;
}

// proposed change to - operator uses a new scalar operator on Vector2.
Vector2 operator-(const Vector2& a, const Vector2& b)
{
	//return Vector2{a.x - b.x, a.y - b.y};
	return a + ((-1.0) * b);
}

// vector < rectangle (vector in bounds)
bool operator<(const Vector2& v, const Rectangle& b)
{
	return (v.x > b.x && b.x + b.width > v.x) && (v.y > b.y && b.y + b.height > v.y);
}

// vector <= rectangle (vector in bounds or on boundary)
bool operator<=(const Vector2& v, const Rectangle& b)
{
	return (v.x >= b.x && b.x + b.width >= v.x) && (v.y >= b.y && b.y + b.height >= v.y);
}

float Vector2SqrMagnitude(const Vector2& x)
{
	return x.x * x.x + x.y * x.y;
}

float Vector2Magnitude(const Vector2& x)
{
	return (float) sqrt( (double)Vector2SqrMagnitude(x) );
}

///////////////////
// Game Specific //
///////////////////
