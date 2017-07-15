#include "material.h"
using namespace std;

void Material::getBRDF(LocalGeo& local, BRDF& brdf) {
    brdf = constantBRDF;
}
