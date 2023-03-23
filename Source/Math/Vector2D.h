#pragma once
#include <math.h>

struct Vector2D
{
public:
    float mX = 0;
    float mY = 0;

    Vector2D()
        : mX(0.0f)
        , mY(0.0f)
    {}

    explicit Vector2D(float x, float y)
        : mX(x)
        , mY(y)
    {}

    void Normalize()
    {
        float lengthSquared = mX * mX + mY * mY;
        float length = sqrtf(lengthSquared);
        mX = mX / length;
        mY = mY / length;
    }

    float GetLength()
    {
        return sqrtf(mX * mX + mY * mY);
    }

    static float Dot(const Vector2D& a, const Vector2D& b)
    {
        return (a.mX * b.mX + a.mY * b.mY);
    }

    Vector2D operator*(float scalar)
    {
        Vector2D temp;
        temp.mX = mX * scalar;
        temp.mY = mY * scalar;
        return temp;
    }
};

inline Vector2D operator-(const Vector2D& a, const Vector2D& b)
{
    return Vector2D(a.mX - b.mX, a.mY - b.mY);
}

inline Vector2D operator+(const Vector2D& a, const Vector2D& b)
{
    return Vector2D(a.mX + b.mX, a.mY + b.mY);
}