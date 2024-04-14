#pragma once
#include "image.h"
#include <functional>

// possible kern_types
enum Kernel_Type {
  Identity,
  Mean_Blur,
  Gausian_Blur,
  Horizontal_Sobel,
  Vertical_Sobel
};

// Kernel class(initalised Kern + scale function)
class Kernel {
  Kernel_Type kern_type;
  unsigned int w, h;

public:
  std::function<void(Image &src)> scale_function;
  double kernel[3][3];
  Kernel();
  void set_kernel(Kernel_Type kern_t);
};

// build kernel
namespace InitKernels {
void identity_kern(Kernel &src);
void mean_blur_kern(Kernel &src);
void gausian_kern(Kernel &src);
void vertical_sobel_kern(Kernel &src);
void horizontal_sobel_kern(Kernel &src);
} // namespace InitKernels

// scale functions for each kernel
namespace scale_functions {
void identity_scale(Image &src);
void mean_blur_scale(Image &src);
void gausian_blur_scale(Image &src);
void sobel_scale(Image &src);
} // namespace scale_functions
