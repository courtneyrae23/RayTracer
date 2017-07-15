#include <vector>
#include <iostream>
#include <fstream>
#include <cmath>

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include "matrix.h"

#define PI 3.14159265 // Should be used from mathlib

void Matrix::calculate_determinant(){
  std::vector<std::vector<float> > to_calc;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < m; j++){
      float val = entries[i][j];
      to_push.push_back(val);
    }
    to_calc.push_back(to_push);
  }
  bool sign = true;
  //std::cout << sign << std::endl;
  for(int l = 0; l < m; l++){
    if(to_calc[l][l] == 0){
      int index = 0;
      for(int j = l+1; j < m; j++){
        if(to_calc[j][l] != 0){
          index = j;
          break;
        }
        if(j == m-1){
          determinant = 0.0;
          return;
        }
      }
      for(int j = 0; j < m; j++){
        float temp = to_calc[l][j];
        to_calc[l][j] = to_calc[index][j];
        to_calc[index][j] = temp;
        sign = not sign;
      }
    }
    for(int i = l+1; i < m; i++){
      float div = to_calc[i][l]/to_calc[l][l];
      if(div == 0){
        continue;
      }
      for(int j = 0; j < m; j++){
        to_calc[i][j] -= div * to_calc[l][j];
      }
    }
  }
  /*for(int i = 0; i < m; i++){
    for(int j = 0; j < m; j++){
      std::cout << to_calc[i][j] << " ";
    }
    std::cout << std::endl;
  }*/
  float to_return = 1.0;
  for(int i = 0; i < m; i++){
    to_return *= to_calc[i][i];
  }
  determinant = to_return;
}

Matrix Matrix::operator*(const Matrix& b){
  //assert(n = b.m);
  std::vector<std::vector<float> > to_return;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < b.n; j++){
      float new_entry = 0;
      for(int k = 0; k < n; k++){
        new_entry += entries[i][k]*b.entries[k][j];
      }
      if(new_entry > -.0000005 and new_entry < .0000005){
        new_entry = 0;
      }
      to_push.push_back(new_entry);
    }
    to_return.push_back(to_push);
  }
  return *(new Matrix(to_return, m, b.n));
}
Matrix Matrix::operator*(const float val){
  std::vector<std::vector<float> > to_return;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < n; j++){
      to_push.push_back(val*entries[i][j]);
    }
    to_return.push_back(to_push);
  }
  return *(new Matrix(to_return, m, n));
}

Point Matrix::operator*(const Point& point){
  Point* p = new Point();
  p->x = (entries[0][0]*point.x) + (entries[0][1]*point.x) + (entries[0][2]*point.x) + (entries[0][3]*1);
  p->y = (entries[1][0]*point.y) + (entries[1][1]*point.y) + (entries[1][2]*point.y) + (entries[1][3]*1);
  p->z = (entries[2][0]*point.z) + (entries[2][1]*point.z) + (entries[2][2]*point.z) + (entries[2][3]*1);
  return *p;
}

Matrix Matrix::operator+(const Matrix& b){
  //assert(m == b.m && n == b.n);
  std::vector<std::vector<float> > to_return;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < n; j++){
      to_push.push_back(entries[i][j]+b.entries[i][j]);
    }
    to_return.push_back(to_push);
  }
  return *(new Matrix(to_return, m, n));
}

Matrix Matrix::operator-(const Matrix& b){
  //assert(m == b.m && n == b.n);
  std::vector<std::vector<float> > to_return;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j= 0; j < n; j++){
      to_push.push_back(entries[i][j]-b.entries[i][j]);
    }
    to_return.push_back(to_push);
  }
  return *(new Matrix(to_return, m, n));
}

Matrix Matrix::RREF(){
  std::vector<std::vector<float> > reduced;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < n; j++){
      to_push.push_back(entries[i][j]);
    }
    reduced.push_back(to_push);
  }
  int lead = 0;
  bool broken = false;
  for(int l = 0; l < m; l++){
    float di, mu;
    if(reduced[l][l] == 0){
      int index = l;
      for(int j = l+1; j < m; j++){
        if(reduced[j][l] != 0){
          index = j;
          break;
        }
      }
      for(int j = 0; j < n; j++){
        float temp = reduced[l][j];
        reduced[l][j] = reduced[index][j];
        reduced[index][j] = temp;
      }
    }
    for(int r = 0; r < m; r++){
      di = reduced[l][lead];
      mu = reduced[r][lead]/reduced[l][lead];
      if(di < .0000005 and di > -.0000005){
        di = 0;
      }
      //std::cout << "lead: " << lead << " l: " << l << " r: " << r << " di: " << di << " mu: " << mu << std::endl;
      if(di == 0){
        lead += 1;
        l -= 1;
        broken = true;
        break;
      }
      for(int c = 0; c < n; c++){
        if(r == l){
          reduced[r][c] /= di;
        } else {
          reduced[r][c] -= reduced[l][c]*mu;
        }
        if(reduced[r][c] == -0){
          reduced[r][c] = 0;
        }
        if(reduced[r][c] < .0000005 and reduced[r][c] > -.0000005){
          reduced[r][c] = 0;
        }
      }
    }
    if(broken == true){
      broken = false;
    } else {
      lead += 1;
    }
  }
  return *(new Matrix(reduced, m, n));
}

Matrix Matrix::transpose(){
  std::vector<std::vector<float> > to_return;
  for(int i = 0; i < n; i++){
    std::vector<float> to_push;
    for(int j = 0; j < m; j++){
      to_push.push_back(entries[j][i]);
    }
    to_return.push_back(to_push);
  }
  return *(new Matrix(to_return, n, m));
}

Matrix Matrix::inverse(){
  //std::cout << "inverse call" << std::endl;
  std::vector<std::vector<float> > to_reduce;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < m; j++){
      to_push.push_back(entries[i][j]);
    }
    for(int j = 0; j < m; j++){
      if(i == j){
        to_push.push_back(1.0);
      } else {
        to_push.push_back(0.0);
      }
    }
    to_reduce.push_back(to_push);
  } 
  Matrix to_split = (*(new Matrix(to_reduce, m, 2*m))).RREF();
  //std::cout << "to_split.print(): " << std::endl;
  //to_split.print();
  std::vector<std::vector<float> > to_return;
  for(int i = 0; i < m; i++){
    std::vector<float> to_push;
    for(int j = 0; j < m; j++){
      to_push.push_back(to_split.entries[i][j+m]);
    }
    to_return.push_back(to_push);
  }
  return *(new Matrix(to_return, m, m));
}

void Matrix::print(){
  for(int i = 0; i < m; i++){
    for(int j = 0; j < n; j++){
      std::cout << entries[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

/*
int main(){
  std::vector<std::vector<float> > to_matrix;
  //float to_push[3][4] = {{1,2,-1,-4},{2,3,-1,-11},{-2,0,-3,22}};
  //float to_push[4][4] = {{1,2,1,1},{3,2,1,0},{5,4,1,2},{0,2,1,1}};
  float to_push[4][4] = {{12,12,12,2},{32,22,12,2},{25,24,21,22},{20,22,12,21}};
  for(int i = 0; i < 4; i++){
    std::vector<float> row;
    for(int j = 0; j < 4; j++){
      row.push_back(to_push[i][j]);
    }
    to_matrix.push_back(row);
  }
  float to_pushb[4][4] = {{1,2,1,3},{2,1,3,1},{4,1,3,1},{3,4,2,1}};
  std::vector<std::vector<float> > to_matrixb;
  for(int i = 0; i < 4; i++){
    std::vector<float> row; 
    for(int j = 0; j < 4; j++){
      row.push_back(to_pushb[i][j]);
    }
    to_matrixb.push_back(row);
  }
  Matrix mat = *(new Matrix(to_matrix, 4, 4));
  Matrix matb = *(new Matrix(to_matrixb, 4, 4));
  Matrix matc = mat.inverse();
  float val = 2*PI/(3*sqrt(3));
  for(float i = 0; i < .3; i += 1){
    Matrix A = *(new Matrix(val+i, val+i, val+i, 2));
    Matrix to_rotate = *(new Matrix(1, 1, 1, 0));
    //std::cout << "YOOOO" << std::endl;
    Matrix result = A*to_rotate;
    std::cout << "i: " << i << std::endl;
    result.print();
  }
  return 1;
}*/