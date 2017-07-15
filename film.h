#include "color.h"
#include "sample.h"
#include <vector>
#include <string>

using namespace std;

class Film {
  public:
    std::vector<std::vector<std::vector<Color> > > film;
    int dimx, dimy;

    Film(int x, int y) {
      dimx = x;
      dimy = y;
      std::vector<std::vector<Color> > row;
      for(int i = 0; i < dimx; i++) {
        std::vector<Color> bucket;
        for (int j = 0; j < dimy; j++) {
          row.push_back(bucket);
        }
        film.push_back(row);
      }
    }

    void commit (Sample&, Color&);
    void writeImage(char*);

};