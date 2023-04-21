// Define once
#ifndef H_VECTORS
#define H_VECTORS

// Includes
#include <iostream>

// Structure
typedef struct Vector2{
  // Variables
  float x,y;

  // Constructor
  Vector2();
  Vector2(float x, float y);

  // Operations
  Vector2 operator+(Vector2 b);
  Vector2 operator*(float b);
  void operator+=(Vector2 b);
  void operator*=(float b);
} Vector2;

// End definition
#endif