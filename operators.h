#ifndef OPERATORS_H_
#define OPERATORS_H_

#include "raylib.h"

#include <cmath>
#include <iostream>
#include <vector>

////////////////////
// Enhanced std:: //
////////////////////

std::ostream& operator<<(std::ostream& os, std::vector<std::string>& v); /**< output vector of strings */
bool is_in(std::vector<std::string> names, std::string str); /**< basic linear search algorithms (STRING) */
bool not_in(std::vector<std::string> names, std::string str); /**< basic linear search algorithms (STRING) */

////////////////////////////
// lib type extensions //
////////////////////////////

Vector2 operator+(const Vector2& a, const Vector2& b); /**< Vector addition */
Vector2 operator*(const float& c, const Vector2& x); /**< Vector scaling */
Vector2 operator-(const Vector2& a, const Vector2& b); /**< Vector subtraction (using scaling) */

bool operator<(const Vector2& v, const Rectangle& b); /**< Vector in bounds check */
bool operator<=(const Vector2& v, const Rectangle& b); /**< Vector in bounds || boundary check */

float Vector2SqrMagnitude(const Vector2& x);  /**< SqrMagnitude of a Vector2 */
float Vector2Magnitude(const Vector2& x);  /**< Magnitude of a Vector2 (MUCH SLOWER) */

///////////////////
// App Specific //
///////////////////


#endif
