#pragma once

class Size {
private:
  unsigned int height, width;
  unsigned int area;

public:
  Size(unsigned int h, unsigned int w);

  unsigned int getHeight() const;
  unsigned int getWidth() const;

  bool operator==(const Size &other) const;
  bool operator>=(const Size &other) const;
  bool operator<=(const Size &other) const;
  bool operator>(const Size &other) const;
  bool operator<(const Size &other) const;
};
