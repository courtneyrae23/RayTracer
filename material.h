#ifndef __MATERIAL_H_INCLUDED__
#define __MATERIAL_H_INCLUDED__

#include "light.h"
#include "localgeo.h"
#include "BRDF.h"

class Material {
    public:
        BRDF constantBRDF;
        Material(BRDF& brdf) {
            constantBRDF = brdf;
        }
        Material() {
            constantBRDF = *(new BRDF());
        }
        void getBRDF(LocalGeo&, BRDF&);
};

#endif