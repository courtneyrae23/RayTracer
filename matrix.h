#ifndef __MATRIX_H_INCLUDED__
#define __MATRIX_H_INCLUDED__


#include <vector>
#include <iostream>
#include "cartesian.h"

#define PI 3.14159265 // Should be used from mathlib

using namespace std;

class Matrix{
  public:
    bool square, invertible;
    int m, n;
    int rts;
    std::vector<std::vector<float> > entries;
    //Matrix(float values[3], bool translation);
    Matrix inverse();
    Matrix transpose();
    Matrix operator+(const Matrix&);
    Matrix operator-(const Matrix&);
    Matrix operator*(const Matrix&);
    Matrix operator*(const float);
    Point operator*(const Point&);
    float determinant;
    Matrix RREF();
    void print();
    void calculate_determinant();

    Matrix(float x, float y, float z, int transformation){
      m = 4;
      n = 4;
      rts = transformation;
      float rx, ry, rz;
      float length = sqrt(x*x + y*y + z*z);
      rx = x/length;
      ry = y/length;
      rz = z/length;
      if(transformation == 2){
        float theta = sqrt(x*x+y*y+z*z)*PI/((float)180);
        float vals[3] = {rx, ry, rz};
        std::vector<std::vector<float> > rrt;
        for(int i = 0; i < 3; i++){
          std::vector<float> to_push;
          for(int j = 0; j < 3; j++){
            to_push.push_back(vals[i]*vals[j]);
          }
          rrt.push_back(to_push);
        }
        Matrix rhatouter = *(new Matrix(rrt, 3, 3));
        std::vector<std::vector<float> > rxvals;
        std::vector<float> row1;
        row1.push_back(0);
        if (rz == 0.0) {
          row1.push_back(0);
        } else {
          row1.push_back(-rz);
        }
        row1.push_back(ry);
        rxvals.push_back(row1);
        std::vector<float> row2;
        row2.push_back(rz);
        row2.push_back(0);
        if (rx == 0.0) {
          row2.push_back(0);
        } else {
          row2.push_back(-rx);
        }
        rxvals.push_back(row2);
        std::vector<float> row3;
        if (ry == 0.0) {
          row3.push_back(0);
        } else {
          row3.push_back(-ry);
        }
        row3.push_back(rx);
        row3.push_back(0);
        rxvals.push_back(row3);
        Matrix rxmat = *(new Matrix(rxvals, 3, 3));
        cout << "rhatouter" << endl;
        rhatouter.print();
        cout << "rxmat" << endl;
        rxmat.print();
        cout << "rxmat squared" << endl;
        (rxmat * rxmat).print();
        Matrix transform = rhatouter + rxmat*sin(theta) - rxmat*rxmat*cos(theta);
        for(int i = 0; i < 3; i++){
          std::vector<float> to_push;
          for(int j = 0; j < 4; j++){
            if(j < 3){
              to_push.push_back(transform.entries[i][j]);
            } else {
              to_push.push_back(0);
            }
          }
          entries.push_back(to_push);
        }
        std::vector<float> to_push;
        for(int i = 0; i < 3; i++){
          to_push.push_back(0);
        }
        to_push.push_back(1);
        entries.push_back(to_push);

        /*std::cout << "theta: " << theta << std::endl;
        std::cout << "x: " << x << " y: " << y << " z: " << z << std::endl;
        std::vector<std::vector<float> > v_entries;
        v_entries.push_back((std::vector<float>) {x});
        v_entries.push_back((std::vector<float>) {y});
        v_entries.push_back((std::vector<float>) {z});
        v_entries.push_back((std::vector<float>) {1});
        Matrix v = *(new Matrix(v_entries, 4, 1));
        Matrix A = *(new Matrix(1,1,1,0));
        std::cout << "transformation == 2: " << std::endl;
        if(z != 0){
          float psi = -acos(y/(sqrt(y*y+z*z)));
          float cospsi = cos(psi);
          float sinpsi = sin(psi);
          std::cout << "PSI: " << psi << std::endl;
          std::cout << "SINPSI: " << sinpsi << std::endl;
          std::cout << "COSPSI: " << cospsi << std::endl;
          std::vector<std::vector<float> > a_entries;
          a_entries.push_back((std::vector<float>) {1,0,0,0});
          a_entries.push_back((std::vector<float>) {0,cospsi, 0-sinpsi, 0});
          a_entries.push_back((std::vector<float>) {0,0+sinpsi, cospsi, 0});
          a_entries.push_back((std::vector<float>) {0,0,0,1});
          A = *(new Matrix(a_entries, 4, 4));
        }
        A.print();
        Matrix Av = A*v;
        std::vector<std::vector<float> > av_entries = Av.entries;
        float phi = -acos(av_entries[0][0]/(sqrt(av_entries[0][0]*av_entries[0][0]+av_entries[1][0]*av_entries[1][0])));
        float cosphi = cos(phi);
        float sinphi = sin(phi);
        if(sinphi*500 > -1 and sinphi * 500 < 1){
          sinphi = 0;
        }
        if(cosphi*500 > -1 and cosphi * 500 < 1){
          cosphi = 0;
        }
        std::cout << "PHI: " << phi << std::endl;
        std::cout << "SINPHI: " << sinphi << std::endl;
        std::cout << "COSPHI: " << cosphi << std::endl;
        std::vector<std::vector<float> > b_entries;
        b_entries.push_back((std::vector<float>) {cosphi, -sinphi, 0, 0});
        b_entries.push_back((std::vector<float>) {sinphi, cosphi, 0, 0});
        b_entries.push_back((std::vector<float>) {0, 0, 1, 0});
        b_entries.push_back((std::vector<float>) {0, 0, 0, 1});
        Matrix B = *(new Matrix(b_entries, 4, 4));
        std::cout << "transformation == 20: " << std::endl;
        B.print();  
        std::vector<std::vector<float> > t_entries;
        float costheta = cos(theta);
        float sintheta = sin(theta);
        std::cout << "THETA: " << theta << std::endl;
        std::cout << "SINTHETA: " << sintheta << std::endl;
        std::cout << "COSTHETA: " << costheta << std::endl;
        if(costheta*500 > -1 and costheta*500 < 1){
          costheta = 0;
        }
        if(sintheta*500 > -1 and sintheta*500 < 1){
          sintheta = 0;
        }
        t_entries.push_back((std::vector<float>) {1, 0, 0, 0});
        t_entries.push_back((std::vector<float>) {0, costheta, 0-sintheta, 0});
        t_entries.push_back((std::vector<float>) {0, sintheta, costheta, 0});
        t_entries.push_back((std::vector<float>) {0, 0, 0, 1});

        Matrix T = *(new Matrix(t_entries, 4, 4));
        std::cout << "T: " << std::endl;
        T.print();
        std::cout << "T*B: " << std::endl;
        (T*B).print();
        
        Matrix BAv = B*Av;
        std::cout<< "B.inverse call" << std::endl;
        Matrix Bi = B.inverse();
        std::cout << "Bi: " << std::endl;
        Bi.print();
        std::cout << "Bi*T*B: " << std::endl;
        (Bi*T*B).print();
        Matrix Ai = A.inverse();
        Matrix AiBiTBA = Ai*Bi*T*B*A;
        Matrix BiBAv = Bi*BAv;
        Matrix AiBiBAv = Ai*BiBAv;
        for(int i = 0; i < 4; i++){
          std::vector<float> to_push;
          for(int j = 0; j < 4; j++){
            to_push.push_back(AiBiTBA.entries[i][j]);
          }
          entries.push_back(to_push);
        }*/
      }
      if(transformation == 0 or transformation == 1 or transformation == 3){
        for(int i = 0; i < 4; i++){
          std::vector<float> to_push;
          for(int j = 0; j < 4; j++){
            if(i == j){
              to_push.push_back(1.0);
            } else {
              to_push.push_back(0.0);
            }
          }
          entries.push_back(to_push);
        }
        if(transformation == 1){
          entries[0][3] = x;
          entries[1][3] = y;
          entries[2][3] = z;
        } else if(transformation == 3){
          entries[0][0] = x;
          entries[1][1] = y;
          entries[2][2] = z;
        }
      }
    }

    Matrix(std::vector<std::vector<float> > entry_list, int rows, int cols){
      m = rows;
      n = cols;
      square = false;
      if(m == n){
        square = true;
      }
      for(int i = 0; i < m; i++){
        std::vector<float> to_add;
        for(int j = 0; j < n; j++){
          to_add.push_back(entry_list[i][j]);
        }
        entries.push_back(to_add);
      }
      if(square){
        calculate_determinant();
      }
      invertible = false;
      if(square && determinant != 0){
        invertible = true;
      }
      rts = 0;
    }

    Matrix() {
        Matrix(0, 0, 0, 0);
    }
};

#endif