# C++ Low Level Design Examples

This repository contains various Low Level Design (LLD) examples implemented in C++. It includes examples of:
- Object-Oriented Programming concepts
- SOLID principles
- Design Patterns
- Basic C++ concepts

## Project Structure

```
.
├── CMakeLists.txt
├── examples/
│   ├── basics/
│   │   ├── lesson1.cpp
│   │   ├── lesson2.cpp
│   │   ├── lesson4.cpp
│   │   ├── lesson5.cpp
│   │   ├── lesson6.cpp
│   │   ├── lesson7.cpp
│   │   ├── lesson8.cpp
│   │   ├── basics.md
│   │   ├── solid.md
│   │   └── designpatterns.md
│   └── parking_lot/
└── README.md
```

## Prerequisites

- CMake (version 3.10 or higher)
- C++ compiler with C++17 support
- Make or Ninja build system

## Building the Project

1. Create a build directory:
```bash
mkdir build
cd build
```

2. Generate build files:
```bash
cmake ..
```

3. Build the project:
```bash
make
```

## Running Examples

After building, you can run any example from the build directory:
```bash
./examples/basics/lesson1
./examples/basics/lesson2
# etc.
```

## Learning Resources

The repository includes markdown files with detailed explanations:
- `basics.md`: C++ OOP concepts
- `solid.md`: SOLID principles
- `designpatterns.md`: Design patterns

## Contributing

Feel free to contribute to this repository by:
1. Forking the repository
2. Creating a new branch
3. Making your changes
4. Submitting a pull request

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Adding New Examples

1. Create a new directory under `examples/` for your example
2. Create a CMakeLists.txt in your example directory
3. Add your source files in the `src/` directory
4. Add your header files in the `include/` directory
5. Update the examples/CMakeLists.txt to include your new example 