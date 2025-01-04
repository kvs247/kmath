# kmath

A personal math library.

## Features

### Core Operations

- `abs`: absolute value of a real number
- `sqrt`: sqaure root of non-negative real number

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
