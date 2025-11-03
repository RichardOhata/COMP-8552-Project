//
// Created by richa on 2025-09-23.
//

#ifndef TEST_VECTOR2D_H
#define TEST_VECTOR2D_H

class Vector2D {
    public:
        float x = 0.0f;
        float y = 0.0f;

    Vector2D() {
        x = 0.0f;
        y = 0.0f;
    }
    Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D& operator+=(const Vector2D& vec);

    Vector2D &operator-=(const Vector2D &vec);

    Vector2D &operator*=(float scalar);

    Vector2D &operator/=(float scalar);

        //Vector2D must be on the left
    Vector2D operator*(float scaler) const;

    friend Vector2D operator*(float scalar, const Vector2D& vec);

    Vector2D operator+(const Vector2D &vec) const;

    Vector2D operator-(const Vector2D &vec) const;

    bool operator==(const Vector2D &vec) const;

    bool operator!=(const Vector2D &vec) const;

    Vector2D operator-() const;

        Vector2D& normalize();
};

#endif //TEST_VECTOR2D_H