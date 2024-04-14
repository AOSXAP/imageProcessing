#include "kernel.h"
#include "image.h"

void scale_functions::sobel_scale(Image &src) {
  for (int i = 0; i < src.height(); i++) {
    for (int j = 0; j < src.width(); j++) {
      src.at(i, j) = (int)((src.at(i, j) + 255 * 4) / 8);
    }
  }
}

void scale_functions::identity_scale(Image &src) {}

void scale_functions::mean_blur_scale(Image &src) {
  for (int i = 0; i < src.height(); i++) {
    for (int j = 0; j < src.width(); j++) {
      src.at(i, j) = (int)((src.at(i, j) / 9));
    }
  }
}

void scale_functions::gausian_blur_scale(Image &src) {
  for (int i = 0; i < src.height(); i++) {
    for (int j = 0; j < src.width(); j++) {
      src.at(i, j) = (int)((src.at(i, j) / 16));
    }
  }
}

Kernel::Kernel() {
  this->w = 3;
  this->h = 3;

  kern_type = Identity;

  for (unsigned int i = 0; i < h; i++) {
    for (unsigned int j = 0; j < w; j++) {
      kernel[i][j] = 0;

      if (i == j) {
        kernel[i][j] = 1;
      }
    }
  }
}

void InitKernels::identity_kern(Kernel &src) {
  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      src.kernel[i][j] = 0;

      if (i == j) {
        src.kernel[i][j] = 1;
      }
    }
  }
}

void InitKernels::mean_blur_kern(Kernel &src) {
  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      src.kernel[i][j] = 1;
    }
  }
}

void InitKernels::gausian_kern(Kernel &src) {
  double gaus_kern[3][3] = {{1, 2, 1}, {2, 4, 2}, {1, 2, 1}};

  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      src.kernel[i][j] = gaus_kern[i][j];
    }
  }
}

void InitKernels::horizontal_sobel_kern(Kernel &src) {
  double h_sobel_kern[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      src.kernel[i][j] = h_sobel_kern[i][j];
    }
  }
}

void InitKernels::vertical_sobel_kern(Kernel &src) {
  double v_sobel_kern[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

  for (unsigned int i = 0; i < 3; i++) {
    for (unsigned int j = 0; j < 3; j++) {
      src.kernel[i][j] = v_sobel_kern[i][j];
    }
  }
}

void Kernel::set_kernel(Kernel_Type kern_t) {
  if (kern_t == Identity) {
    InitKernels::identity_kern(*this);
    scale_function = scale_functions::identity_scale;
  } else if (kern_t == Mean_Blur) {
    InitKernels::mean_blur_kern(*this);
    scale_function = scale_functions::mean_blur_scale;
  } else if (kern_t == Gausian_Blur) {
    InitKernels::gausian_kern(*this);
    scale_function = scale_functions::gausian_blur_scale;
  } else if (kern_t == Vertical_Sobel) {
    InitKernels::vertical_sobel_kern(*this);
    scale_function = scale_functions::sobel_scale;
  } else if (kern_t == Horizontal_Sobel) {
    InitKernels::horizontal_sobel_kern(*this);
    scale_function = scale_functions::sobel_scale;
  }
}
