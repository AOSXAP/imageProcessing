#include "process.h"
#include "image.h"
#include "kernel.h"
#include <cmath>

BrightnessFilter::BrightnessFilter(double a, double b) {
  alpha = a;
  beta = b;
}

void BrightnessFilter::process(const Image &src, Image &dst) {
  // brighness
  for (int i = 0; i < src.m_height - 1; i++) {
    for (int j = 0; j < src.m_width - 1; j++) {
      dst.m_data[i][j] =
          ((int)(src.m_data[i][j] * this->alpha + this->beta) % 256);
    }
  }
}
GammaFilter::GammaFilter(double y) { this->gamma = y; }

void GammaFilter::process(const Image &src, Image &dst) {

  for (int i = 0; i < src.m_height; i++) {
    for (int j = 0; j < src.m_width; j++) {
      dst.m_data[i][j] =
          (unsigned int)pow((src.m_data[i][j]), this->gamma) % 255;
    }
  }
}

Convulution::Convulution(Kernel_Type kern_type) {
  w_kernel = 3;
  h_kernel = 3;

  Kernel kern;
  kern.set_kernel(kern_type);

  scale = kern.scale_function;

  for (int i = 0; i < h_kernel; i++) {
    for (int j = 0; j < w_kernel; j++) {
      kernel[i][j] = kern.kernel[i][j];
    }
  }
}

void Convulution::process(const Image &src, Image &dst) {
  for (int i = 0; i < src.m_height; i++) {
    for (int j = 0; j < src.m_width; j++) {
      double sum = 0;
      int k = this->w_kernel * this->h_kernel;

      for (int u = 0; u < this->h_kernel; u++) {
        for (int v = 0; v < this->w_kernel; v++) {
          if (i - u + k < src.m_height and j - v + k < src.m_width)
            sum += this->kernel[u][v] * src.m_data[i - u + k][j - v + k];
        }
      }

      dst.m_data[i][j] = (int)sum;
    }
  }
  scale(dst);
}

void Drawing::drawLine(Image &src, Point p1, Point p2, double color_freq) {
  double slope =
      atan((double)(p2.getY() - p1.getY()) / (double)(p2.getX() - p1.getX()));

  double n = p1.getY() - p1.getX() * slope;

  for (int i = p1.getX(); i < p2.getX(); i++) {
    int y = i * slope + n;

    if (i < src.height() and y < src.width())
      src.at(y, i) = color_freq;
  }

  if (p1.getX() == p2.getX()) {
    for (int y = p1.getY(); y < p2.getY(); y++) {
      src.at(y, p1.getX()) = color_freq;
    }
  }
};

void Drawing::DrawCircle(Image &img, Point center, int radius,
                         double color_freq) {
  for (int i = 0; i < 360; i++) {
    int x = cos(i) * radius, y = sin(i) * radius;
    img.at(center.getY() + y, center.getX() + x) = color_freq;
  }
}

void Drawing::drawRectangle(Image &img, Point center, int br,
                            double color_freq) {
  Point left_corner(center.getX() - br / 2, center.getY() - br / 2);
  Point right_corner(left_corner.getX() + br, left_corner.getY());
  Point left_down_corner(left_corner.getX(), left_corner.getY() + br);
  Point right_down_corner(left_corner.getX() + br, left_corner.getY() + br);

  drawLine(img, left_corner, right_corner, color_freq);

  drawLine(img, left_corner, left_down_corner, color_freq);

  drawLine(img, left_down_corner, right_down_corner, color_freq);

  drawLine(img, right_corner, right_down_corner, color_freq);
}
