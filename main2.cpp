// reading a text file
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <vector>
#include "cartesian.h"
#include "material.h"
#include "scene.h"
#include "primitive.h"
#include "shapes.h"
#include "localgeo.h"
#include "light.h"
#include "parser.h"
using namespace std;


std::vector<Primitive*> primitives;
std::vector<Light*> lights;
Material* currMaterial;
std::vector<Matrix> transform;
int dimx, dimy;
Scene myScene;

void createSphere(float cx, float cy, float cz, float r) {
    Point* p = new Point(cx, cy, cz);
    Sphere* sphere = new Sphere(*p, r);
    Point currCenter = *(new Point(cx, cy, cz));
    Matrix m = *(new Matrix(0,0,0,0));
    for(int i = transform.size()-1; i > -1; i--){
        Matrix to_apply = transform[i];
        if(to_apply.rts == 1){
            currCenter = to_apply * currCenter;
            m = to_apply * m;
        } else {
            Matrix t_to_o = *(new Matrix(-currCenter.x, -currCenter.y, -currCenter.z, 1));
            Matrix o_to_t = *(new Matrix(currCenter.x, currCenter.y, currCenter.z, 1));
            m = o_to_t * transform[i] * t_to_o * m;
            //m = transform[i] * m;
        }
    }
    Transformation* oTw = new Transformation(m, m.inverse().transpose());
    Transformation* wTo = new Transformation(m.inverse(), m.transpose());
    GeometricPrimitive* sph = new GeometricPrimitive(*oTw, *wTo, sphere, currMaterial); 
    primitives.push_back(sph);
}

void createTriangle(Point* A, Point* B, Point* C) {
    Triangle* triangle = new Triangle(A, B, C);
    Vector b_a = *B - *A;
    Vector c_a = *C - *A;
    Point currCenter = (*A) + (b_a)*((float) 0.3333) + (c_a)*((float) 0.3333);
    std::vector<Matrix>::iterator iter;
    int i = transform.size() - 1;
    Matrix m = *(new Matrix(0, 0, 0, 0));
    for (iter = transform.begin(); iter != transform.end(); iter++) {
        if (transform[i].rts = 1) {
            currCenter = transform[i] * currCenter;
            m = transform[i] * m;
        } else {
            Matrix t_to_o = *(new Matrix(-currCenter.x, -currCenter.y, -currCenter.z, 1));
            Matrix o_to_t = *(new Matrix(currCenter.x, currCenter.y, currCenter.z, 1));
            m = o_to_t * transform[i] * t_to_o * m;
        }
        i--;
    }
    Transformation* oTw = new Transformation(m, m.inverse().transpose());
    Transformation* wTo = new Transformation(m.inverse(), m.transpose());
    GeometricPrimitive* tri = new GeometricPrimitive(*oTw, *wTo, triangle, currMaterial); 
    primitives.push_back(tri);
}

void createScene(Point* e, Point* LL, Point* LR, Point* UL, Point* UR){
    myScene = *(new Scene(e, LL, LR, UL, UR, dimx, dimy));
}

void createPtLight(Point p, Color c, int f) {
    Light* l = new Light(p, c, f, true, false, false);
    lights.push_back(l);
}

void createDirLight(Point p, Color c) {
    Light* l = new Light(p, c, 0, false, true, false);
    lights.push_back(l);
}

void createAmbLight(Color c) {
    Light* l = new Light(*(new Point()), c, 0, false, false, true);
    lights.push_back(l);
}

int main(int argc, char *argv[]) {
    dimx = 800;
    dimy = 800;
    Matrix id = *(new Matrix(0,0,0,0));
    transform.push_back(*(new Matrix(0,0,0,0)));
    id.print();
    string valid_commands[] = {"cam", "sph", "tri", "obj", "ltp", "ltd", "lta", "mat", "xft", "xfr", "xfs", "xfz"}; 
    char* file = argv[1];
    string filen = *(new string(file));
    filen.replace(0,5,"image");
    filen += ".png";
    string line;
    ifstream myfile (file);
    if (myfile.is_open()) {
        while ( getline (myfile,line) ) {
            istringstream iss(line);
            string word;
            string extra;
            iss >> word;
            if (word == valid_commands[0]) {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                Point* eye = new Point(x, y, z);
                iss >> x;
                iss >> y;
                iss >> z;
                Point* LL = new Point(x, y, z);
                iss >> x;
                iss >> y;
                iss >> z;
                Point* LR = new Point(x, y, z);
                iss >> x;
                iss >> y;
                iss >> z;
                Point* UL = new Point(x, y, z);
                iss >> x;
                iss >> y;
                iss >> z;
                Point* UR = new Point(x, y, z);
                createScene(eye, LL, UL, LR, UR);
            } else if (word == valid_commands[1]) {
                float x, y, z, r;
                iss >> x;
                iss >> y;
                iss >> z;
                iss >> r;
                createSphere(x, y, z, r);
            } else if (word == valid_commands[2]) {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                Point* A = new Point(x, y, z);
                iss >> x;
                iss >> y;
                iss >> z;
                Point* B = new Point(x, y, z);
                iss >> x;
                iss >> y;
                iss >> z;
                Point* C = new Point(x, y, z);
                createTriangle(A, B, C);
            } else if (word == valid_commands[3]) {
                string filename;
                iss >> filename;
                std::vector<Triangle> t;
                Parser p = *(new Parser());
                p.parse(filename, t);
                std::vector<Triangle>::iterator iter;
                int i = 0;
                for (iter = t.begin(); iter != t.end(); iter++) {
                    createTriangle(&(t[i].v1), &(t[i].v2), &(t[i].v3));
                    i++;
                }
            } else if (word == valid_commands[4]) {
                float x, y, z;
                float r, g, b;
                iss >> x;
                iss >> y;
                iss >> z;
                Point * p = new Point(x, y, z);
                iss >> r;
                iss >> g;
                iss >> b;
                Color * c = new Color(r, g, b);
                int falloff = 0;
                //cout << "create point light: " << x << " " << y << " " << z << " " << r << " " << g << " " << b << endl;
                if (iss >> falloff) {
                    createPtLight(*p, *c, falloff);
                } else {
                    createPtLight(*p, *c, 0);
                }
            } else if (word == valid_commands[5]) {
                float x, y, z;
                float r, g, b;
                iss >> x;
                iss >> y;
                iss >> z;
                Point * p = new Point(x, y, z);
                iss >> r;
                iss >> g;
                iss >> b;
                Color * c = new Color(r, g, b);
                createDirLight(*p, *c);
            } else if (word == valid_commands[6]) {
                float r, g, b;
                iss >> r;
                iss >> g;
                iss >> b;
                Color * c = new Color(r, g, b);
                createAmbLight(*c);
            } else if (word == valid_commands[7]) {
                float r, g, b, sp;
                iss >> r;
                iss >> g;
                iss >> b;
                Color * ka = new Color(r, g, b);
                iss >> r;
                iss >> g;
                iss >> b;
                Color * kd = new Color(r, g, b);
                iss >> r;
                iss >> g;
                iss >> b;
                iss >> sp;
                Color * ks = new Color(r, g, b);
                iss >> r;
                iss >> g;
                iss >> b;
                Color * kr = new Color(r, g, b);
                BRDF* brdf = new BRDF(*ka, *kd, *ks, *kr, sp);
                currMaterial = new Material(*brdf);
            } else if (word == valid_commands[8]) {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                transform.push_back(*(new Matrix(x, y, z, 1)));
            } else if (word == valid_commands[9]) {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                transform.push_back(*(new Matrix(x, y, z, 2))); 
            } else if (word == valid_commands[10]) {
                float x, y, z;
                iss >> x;
                iss >> y;
                iss >> z;
                transform.push_back(*(new Matrix(x, y, z, 3)));
            } else if (word == valid_commands[11]) {
                transform.clear();
                transform.push_back(*(new Matrix(0, 0, 0, 0)));
            } else {
                cout << "Warning: Unrecognized type in line" << endl;
                continue;
            }

            if (iss >> extra) {
                cout << "Warning: Extra parameters in line" << endl;
            }
        }
    }

    myfile.close();
    cout << lights[0] <<endl;
    char *cstr = new char[filen.length() + 1];
    strcpy(cstr, filen.c_str());
    myScene.render(lights, primitives, cstr);
}
           

