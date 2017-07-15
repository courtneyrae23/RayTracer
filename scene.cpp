// Scene.cpp
#include <iostream>
#include "scene.h"
#include "light.h"
#include "primitive.h"
#include "raytracer.h"
#include "film.h"
using namespace std;

void Scene::render(std::vector<Light*> lights, std::vector<Primitive*> primitives, char* filename) {

  Sampler* sampler = new Sampler(dimx, dimy);
  Sample* sample = new Sample();
  Camera* camera = new Camera(eye, LL, UL, LR, UR, dimx, dimy);
  RayTracer* raytracer = new RayTracer(lights, primitives);
  Ray* ray = new Ray();

  Film* film = new Film(dimx, dimy);
  //cout << "checkpoint 1" << endl;
  while (sampler->generateSample(sample)) {
    Color* color = new Color();
    camera->generateRay(*sample, ray);
    //cout << "ray generated: " << endl;
    //cout << sample->x << " " << sample->y << endl;
    //ray->pos.print();
    //ray->dir.print();
    raytracer->trace(*ray, 0, *color);
    //color->print();
    film->commit(*sample, *color);
  }
  //cout << "checkpoint 2" << endl;
  film->writeImage(filename);
}


