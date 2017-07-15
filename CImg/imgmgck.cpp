#include "CImg.h"
#include <stdio.h>
#include <stdlib.h>

using namespace cimg_library;

int main(int argc, char **argv){
	CImg<unsigned char> img(100,100,1,3);
	cimg_forXYC(img, x, y, c) { 
		img(x,y,c) = 0;
	}
	img(49,49,0) = 255;
	img(49,49,1) = 255;
	img(50,50,0) = 255;
	img(50,50,1) = 255;
	img(49,50,0) = 255;
	img(49,50,1) = 255;
	img(50,49,0) = 255;
	img(50,49,1) = 255;
	img.display("Color gradient");
	img.save("file.png");
}