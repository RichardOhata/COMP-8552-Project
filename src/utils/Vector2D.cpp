//
// Created by richa on 2025-09-23.
//

#include "Vector2D.h"

#include <cmath>


Vector2D& Vector2D::operator+=(const Vector2D &vec) {
    this->x += vec.x;
    this->y += vec.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D &vec) {
    this->x -= vec.x;
    this->y -= vec.y;
    return *this;
}

Vector2D& Vector2D::operator*=(float scalar) {
    this->x *= scalar;
    this->y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(float scalar) {
    this->x /= scalar;
    this->y /= scalar;
    return *this;
}


Vector2D Vector2D::operator*(float scaler) const {
    return Vector2D (x * scaler, y * scaler);
}

Vector2D operator*(float scaler, const Vector2D& vec) {
    return Vector2D (vec.x * scaler, vec.y * scaler);
}

Vector2D Vector2D::operator+(const Vector2D& vec) const {
    return Vector2D(this->x + vec.x, this->y + vec.y);
}

Vector2D Vector2D::operator-(const Vector2D& vec) const {
    return Vector2D(this->x - vec.x, this->y - vec.y);
}

bool Vector2D::operator==(const Vector2D& vec) const {
    return this->x == vec.x && this->y == vec.y;
}

bool Vector2D::operator!=(const Vector2D& vec) const {
    return !(*this == vec);
}

Vector2D Vector2D::operator-() const {
    return Vector2D(-x, -y);
}

Vector2D &Vector2D::normalize() {
    float length = sqrt(x * x + y * y);

    // If the length was 4.4
    // x = x/4.4
    if (length > 0) {
        this->x /= length;
        this->y /= length;
    }

    return *this;
}

float Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::lerp(const Vector2D& target, float t) const {
    return Vector2D(x + (target.x - x) * t, y + (target.y - y) * t);
}
