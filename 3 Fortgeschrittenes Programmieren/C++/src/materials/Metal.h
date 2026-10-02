#pragma once
#include "Material.h"

class Metal : public Material {
public:
    Metal() {
        price = 800;
        name = "Metall";
    }
};
