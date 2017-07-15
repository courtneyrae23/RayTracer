#include "film.h"
#include "CImg.h"
#include <vector>
#include <iostream> 
using namespace std;
using namespace cimg_library;


void Film::commit (Sample& sample, Color& color) {
  film[sample.x][sample.y].push_back(color);
}

void Film::writeImage (char* filename) {
  CImg<unsigned char> to_file(dimx, dimy, 1, 3);
  for (int i = 0; i < dimx; i++) {
    for (int j = 0; j < dimy; j++) {
    	std::vector<Color> bucket = film[i][j];
      std::vector<Color>::iterator iter;
   		Color total;
   		int k = 0;
      for (iter = bucket.begin(); iter != bucket.end(); iter++) {
      	total = total + bucket[k];
      	k++;
      }
      total = total * (1.0 / (k));
      float color[] = {total.r*255, total.g*255, total.b*255};
      for(int k = 0; k < 3; k++){
        if(color[k] > 255){
          color[k] = 255;
        }
      }
      to_file.draw_point(i, dimy-j, color);
      /*to_file(j, i, 0) = total.r;
      to_file(j, i, 1) = total.g;
      to_file(j, i, 2) = total.b;*/
    }
  } 
  //to_file.display("BOOYAH");
  to_file.save(filename);
  cout << "Saved" << endl;
}

// int main(int argc, char **argv){
//   Film f = *(new Film(100,100));
//   for(int i = 0; i < 100; i++){
//     for(int j = 0; j < 100; j++){
//       f.film[i][j].push_back(new Color(255.0, 255.0, 0.0));
//     }
//   }
//   f.writeImage();
//   return 0;
// }