#pragma once

#include <string>
#include <memory>

// Abstract base class
class Shape {
public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual std::string getName() const = 0;
};

// Concrete class for Circle
class Circle : public Shape {
public:
    Circle(double radius);
    double getArea() const override;
    std::string getName() const override;

private:
    double radius;
};

// Concrete class for Rectangle
class Rectangle : public Shape {
public:
    Rectangle(double width, double height);
    double getArea() const override;
    std::string getName() const override;

private:
    double width;
    double height;
}; 