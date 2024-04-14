#include "image.h"
#include "size.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using std::ifstream;
using std::ofstream;

Image::Image() {
  m_data = nullptr;
  m_width = 0;
  m_height = 0;
}

Image::Image(unsigned int w, unsigned int h) {
  m_data = nullptr;
  m_width = w;
  m_height = h;

  m_data = new double *[h];
  for (int i = 0; i < h; i++) {
    m_data[i] = new double[w];
    for (int j = 0; j < w; j++) {
      m_data[i][j] = 0;
    }
  }
}

Image::Image(const Image &other) {
  this->m_data = other.m_data;
  this->m_width = other.m_width;
  this->m_height = other.m_height;
}

Image::~Image() {
  if (m_data) {
    for (int i = 0; i < m_height; i++) {
      delete[] m_data[i];
    }

    delete[] m_data;
    m_data = nullptr;
  }
}

Size Image::size() const { return Size(m_width, m_height); }

unsigned int Image::width() const { return m_width; }

unsigned int Image::height() const { return m_height; }

void Image::setWidth(unsigned int w) { m_width = w; }

void Image::setHeight(unsigned int h) { m_height = h; }

bool Image::isEmpty() const {
  bool is_empty = (m_data == nullptr) && (m_width == 0) && (m_height == 0);

  return is_empty;
}

std::ostream &operator<<(std::ostream &os, const Image &image) {
  os << "P2"
     << "\n"
     << "# PGM File"
     << "\n";

  os << image.m_width << " " << image.m_height << "\n";
  os << 255 << "\n";

  for (int i = 0; i < image.m_height; i++) {
    for (int j = 0; j < image.m_width; j++) {
      os << image.m_data[i][j] << " ";
    }
    os << "\n";
  }

  return os;
}

std::istream &operator>>(std::istream &is, Image &dt) {
  char format[1024], comment[1024];
  unsigned int w, h, max_pixel_val;

  is.getline(format, sizeof(format));
  is.getline(comment, sizeof(comment));

  is >> w;
  is >> h;
  is >> max_pixel_val;

  dt.m_width = w;
  dt.m_height = h;

  if (dt.m_data) {
    for (int i = 0; i < dt.m_height; i++) {
      delete[] dt.m_data[i];
    }
    delete[] dt.m_data;
    dt.m_data = nullptr;
  }

  dt.m_data = new double *[h];

  for (int i = 0; i < h; i++) {
    dt.m_data[i] = new double[w];
    for (int j = 0; j < w; j++) {
      is >> dt.m_data[i][j];
    }
  }

  return is;
}

bool Image::load(std::string filename) {
  ifstream is(filename);

  if (!is.is_open())
    return false;

  is >> *this;
  is.close();
  return true;
}

bool Image::save(std::string filename) const {
  ofstream os(filename);
  if (!os.is_open())
    return false;

  os << *this;
  os.close();

  return true;
}

void Image::getData() {
  for (int i = 0; i < this->m_height; i++) {
    for (int j = 0; j < this->m_width; j++)
      std::cout << this->m_data[i][j] << " ";
    std::cout << std::endl;
  }
}

double &Image::at(unsigned int x, unsigned int y) { return this->m_data[x][y]; }

double &Image::at(Point x) { return this->m_data[x.getX()][x.getY()]; }

void Image::InitDefImg(unsigned int def) {
  if (m_data == nullptr) {
    m_data = new double *[this->m_height];
  }
  for (int i = 0; i < this->m_height; i++) {
    if (m_data[i] == nullptr) {
      m_data[i] = new double[this->m_width];
    }

    for (int j = 0; j < this->m_width; j++) {
      m_data[i][j] = def;
    }
  }
}

Image Image::zeroes(unsigned int w, unsigned int h) {
  Image img(w, h);
  img.InitDefImg(0);
  return img;
}

Image Image::ones(unsigned int w, unsigned int h) {
  Image img(w, h);
  img.InitDefImg(1);
  return img;
}

double *Image::row(int y) { return this->m_data[y]; }

Image Image::operator+(const Image &im) {
  if (this->m_width == im.m_width && this->m_height == im.m_height) {
    unsigned int w = im.m_width;
    unsigned int h = im.m_height;

    Image new_img(w, h);

    for (int i = 0; i < this->m_height; i++) {
      for (int j = 0; j < this->m_width; j++) {
        new_img.m_data[i][j] = this->m_data[i][j] + im.m_data[i][j];
      }
    }

    return new_img;
  }

  throw std::invalid_argument("Images are not same size");
}

Image Image::operator-(const Image &im) {
  if (this->m_width == im.m_width && this->m_height == im.m_height) {
    Image new_img(this->m_width, this->m_height);

    for (int i = 0; i < this->m_height; i++) {
      for (int j = 0; j < this->m_width; j++) {
        new_img.m_data[i][j] = this->m_data[i][j] - im.m_data[i][j];
      }
    }

    return new_img;
  }

  throw std::invalid_argument("Images are not same size");
}

Image Image::operator*(double s) {
  for (int i = 0; i < this->m_height; i++) {
    for (int j = 0; j < this->m_width; j++) {
      this->m_data[i][j] *= s;
    }
  }

  return *this;
}
