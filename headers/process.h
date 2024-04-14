#include "image.h"
#include "kernel.h"
#include <functional>

class ImageProcess {
public:
  virtual void process(const Image &src, Image &dst){};
};

class BrightnessFilter : public ImageProcess {
private:
  double alpha = 1;
  double beta = 0;

public:
  BrightnessFilter(double a, double b);
  void process(const Image &src, Image &dst) override;
};

class GammaFilter : public ImageProcess {
private:
  double gamma = 1;

public:
  GammaFilter(double y);
  void process(const Image &src, Image &dst) override;
};

class Convulution : public ImageProcess {
  int w_kernel, h_kernel;
  double kernel[100][100];
  std::function<void(Image &)> scale;

public:
  Convulution(Kernel_Type kern_type);
  void process(const Image &src, Image &dst) override;
};

class Drawing {
public:
  void drawLine(Image &img, Point p1, Point p2, double color_freq);
  void DrawCircle(Image &img, Point center, int radius, double color_freq);
  void drawRectangle(Image &img, Rectangle r, double color_freq);
  void drawRectangle(Image &img, Point tl, int br, double color_freq);
};
