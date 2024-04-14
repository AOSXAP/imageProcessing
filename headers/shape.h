#pragma once

#include <algorithm>

class Point {
private:
  int x;
  int y;

public:
  // Default constructor
  Point() : x(0), y(0) {}

  // Parameterized constructor
  Point(int x, int y) : x(x), y(y) {}

  // Getter for x coordinate
  int getX() const { return x; }

  // Setter for x coordinate
  void setX(int x) { this->x = x; }

  // Getter for y coordinate
  int getY() const { return y; }

  // Setter for y coordinate
  void setY(int y) { this->y = y; }

  // Overloading addition operator
  Point operator+(const Point &p) const { return Point(x + p.x, y + p.y); }

  // Overloading subtraction operator
  Point operator-(const Point &p) const { return Point(x - p.x, y - p.y); }
};

class Rectangle {
private:
  int x;
  int y;
  int width;
  int height;

public:
  // Default constructor
  Rectangle() : x(0), y(0), width(0), height(0) {}

  // Parameterized constructor
  Rectangle(int x, int y, int width, int height)
      : x(x), y(y), width(width), height(height) {}

  // Getter for x coordinate
  int getX() const { return x; }

  // Setter for x coordinate
  void setX(int x) { this->x = x; }

  // Getter for y coordinate
  int getY() const { return y; }

  // Setter for y coordinate
  void setY(int y) { this->y = y; }

  // Getter for width
  int getWidth() const { return width; }

  // Setter for width
  void setWidth(int width) { this->width = width; }

  // Getter for height
  int getHeight() const { return height; }

  // Setter for height
  void setHeight(int height) { this->height = height; }

  // Overloading addition operator to translate the rectangle
  Rectangle operator+(const Point &p) const {
    return Rectangle(x + p.getX(), y + p.getY(), width, height);
  }

  // Overloading subtraction operator to translate the rectangle
  Rectangle operator-(const Point &p) const {
    return Rectangle(x - p.getX(), y - p.getY(), width, height);
  }

  // Overloading binary AND operator to compute intersection
  Rectangle operator&(const Rectangle &other) const {
    int x1 = std::max(x, other.x);
    int y1 = std::max(y, other.y);
    int x2 = std::min(x + width, other.x + other.width);
    int y2 = std::min(y + height, other.y + other.height);
    if (x1 < x2 && y1 < y2) {
      return Rectangle(x1, y1, x2 - x1, y2 - y1);
    } else {
      // No intersection
      return Rectangle();
    }
  }

  // Overloading binary OR operator to compute union
  Rectangle operator|(const Rectangle &other) const {
    int x1 = std::min(x, other.x);
    int y1 = std::min(y, other.y);
    int x2 = std::max(x + width, other.x + other.width);
    int y2 = std::max(y + height, other.y + other.height);
    return Rectangle(x1, y1, x2 - x1, y2 - y1);
  }
};
