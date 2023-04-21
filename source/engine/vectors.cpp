// Header
#include <engine/vectors.h>

// Constructor
Vector2::Vector2(){
  x = 0;
  y = 0;
}
Vector2::Vector2(float x, float y){
  this->x = x;
  this->y = y;
}

// Operations
Vector2 Vector2::operator+(Vector2 b){
  return Vector2(x + b.x, y + b.y);
}
Vector2 Vector2::operator*(float b){
  return Vector2(x * b, y * b);
}
void Vector2::operator+=(Vector2 b){
  x += b.x; y += b.y;
}
void Vector2::operator*=(float b){
  x *= b; y *= b;
}