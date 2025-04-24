#include "shape.h"
#include <iostream>
#include <vector>
#include <memory>

void printShapeInfo(const Shape& shape) {
    std::cout << "Shape: " << shape.getName() << "\n";
    std::cout << "Area: " << shape.getArea() << "\n\n";
}

int main() {
    // Create a vector of shapes using smart pointers
    std::vector<std::unique_ptr<Shape>> shapes;
    
    // Add some shapes
    shapes.push_back(std::make_unique<Circle>(5.0));
    shapes.push_back(std::make_unique<Rectangle>(4.0, 6.0));
    shapes.push_back(std::make_unique<Circle>(3.0));
    
    // Print information about each shape
    std::cout << "Shape Information:\n";
    std::cout << "-----------------\n";
    for (const auto& shape : shapes) {
        printShapeInfo(*shape);
    }
    
    return 0;
} 