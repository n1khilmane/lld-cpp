#include "shape.h"
#include <cmath>

Circle::Circle(double radius) : radius(radius) {}

double Circle::getArea() const {
    return M_PI * radius * radius;
}

std::string Circle::getName() const {
    return "Circle";
}

Rectangle::Rectangle(double width, double height)
    : width(width), height(height) {}

double Rectangle::getArea() const {
    return width * height;
}

std::string Rectangle::getName() const {
    return "Rectangle";
} 