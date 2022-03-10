#pragma once


class Vector2D {
    float x;
    float y;

public:

    Vector2D(float x, float y);

    Vector2D();

    ~Vector2D() = default;

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    friend Vector2D operator+(Vector2D a, Vector2D b);

    friend Vector2D operator-(Vector2D a, Vector2D b);

    Vector2D *operator+=(Vector2D a);

    Vector2D *operator-=(Vector2D a);

    Vector2D *MultiplyByN(float n);

};

