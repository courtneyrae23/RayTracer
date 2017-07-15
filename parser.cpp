#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include "shapes.h"
#include "parser.h"

using namespace std;

#define PI 3.14159265 // Should be used from mathlib

void Parser::parse(string filename, std::vector<Triangle>& triangle_list){
  std::vector<Point> vertex_list;
  ifstream objfile(filename);
  string line;
  cout << filename << endl;
  if(objfile.is_open()){
    while(getline(objfile, line)){
      istringstream iss(line);
      string arg;
      iss >> arg;
      if(arg == "v"){
        float x, y, z;
        iss >> x;
        iss >> y;
        iss >> z;
        vertex_list.push_back(*(new Point(x, y, z)));
      } else if(arg == "f"){
        std::vector<Point*> vertices;
        float val;
        while(iss >> val){
          vertices.push_back(&(vertex_list[val-1]));
        }
        for(int i = 1; i < vertices.size()-1; i++){
          Triangle* t = new Triangle(vertices[0], vertices[i], vertices[i+1]);
          triangle_list.push_back(*t);
        }
      }
    }
  }
}