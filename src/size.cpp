#include "size.h"

Size::Size(unsigned int w, unsigned int h) : height(h), width(w) {
  area = w * h;
}

unsigned int Size::getWidth() const { return this->width; }
unsigned int Size::getHeight() const { return this->height; }

bool Size::operator==(const Size &other) const {
  if (this->area == other.area)
    return true;
  return false;
}

bool Size::operator>=(const Size &other) const {
  if (this->area >= other.area)
    return true;
  return false;
}

bool Size::operator<=(const Size &other) const {
  if (this->area <= other.area)
    return true;
  return false;
}

bool Size::operator>(const Size &other) const {
  if (this->area > other.area)
    return true;
  return false;
}

bool Size::operator<(const Size &other) const {
  if (this->area < other.area)
    return true;
  return false;
}
