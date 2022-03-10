#include "Vector2D.h"

Vector2D::Vector2D() {
    x = 0.0f;
    y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
    this->x = x;
    this->y = y;
}

Vector2D operator+(Vector2D a, Vector2D b) {
    Vector2D tmp;

    tmp.x = a.x + b.x;
    tmp.y = a.y + b.y;

    return tmp;
}

Vector2D operator-(Vector2D a, Vector2D b) {
    Vector2D tmp;

    tmp.x = a.x - b.x;
    tmp.y = a.y - b.y;

    return tmp;
}

Vector2D *Vector2D::operator+=(Vector2D a) {
    this->x += a.x;
    this->y += a.y;

    return this;
}

Vector2D *Vector2D::operator-=(Vector2D a) {
    this->x -= a.x;
    this->y -= a.y;

    return this;
}

float Vector2D::getX() const {
    return x;
}

void Vector2D::setX(float x) {
    this->x = x;
}

float Vector2D::getY() const {
    return y;
}

void Vector2D::setY(float y) {
    this->y = y;
}

Vector2D *Vector2D::MultiplyByN(float n) {
    x *= n;
    y *= n;

    return this;
}
