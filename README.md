# kmath

A personal math library.

## Features

### Core Operations

- `abs`: absolute value of a real number
- `sqrt`: sqaure root of non-negative real number
- `max`: maximum value between two floats
- `min`: minimum value between two floats

### Trig Operations

- `reduceRad`: convert radians to the range (-π, π]
- `reduceDeg`: convert degrees to the range (-180, 180]
- `degToRad`: convert degrees to radians in range (-π, π]
- `radToDeg`: convert radians to degrees in range (-180, 180]
- `polarToCart`: conver polar (radius, angle) coordinate to cartesian (x, y) coordinate
- `cartToPolar`: convert cartesian (x, y) to polar (radius, angle) coordinate
- `sin`
- `cos`

### Matrix Operations

- Comprehensive `Matrix` class
  - Basic arithmetic operations
  - transposition

### Vector Operations

- Specialized `Vector` subclass of `Matrix` (matrix column vector)
  - Basic arithmetic operations
  - Inner product
  - Normalization

### Matrix Decomposition

- QR Decompositon
  - Gram-Schmidt orthogonalization process

### Eigenvalue Analysis

- `Eigen` class for eigenvalue computation
  - Eigenvalue/eigenvector calculation

## Requirements

- C++11 compatible compiler
- CMake 3.28+

## Building

```bash
git clone https://github.com/kvs247/kmath.git
cd kmath
mkdir build && cd build
cmake .. && make
```

## Testing

```bash
ctest
```
