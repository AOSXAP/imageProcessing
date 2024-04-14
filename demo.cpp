#include "headers/image.h"
#include "headers/kernel.h"
#include "headers/process.h"
#include <string>
using namespace std;

void demo() {
  Image im;
  im.load("imgs/img5.pgm");
  int i = 5;

  for (auto kern_type :
       {Mean_Blur, Gausian_Blur, Vertical_Sobel, Horizontal_Sobel}) {
    Convulution gd(kern_type);
    Image n(im.width(), im.height());
    gd.process(im, n);

    BrightnessFilter f(1.9, 0);
    f.process(n, im);

    Drawing dr;

    int randX = rand() % 500, randY = rand() % 500, randR = rand() % 80;
    dr.DrawCircle(im, Point(randX, randY), randR, 255);

    string path = "imgs/results/convul" + to_string(i++) + ".pgm";
    im.save(path);
  }
}

int main(){
  demo();
}