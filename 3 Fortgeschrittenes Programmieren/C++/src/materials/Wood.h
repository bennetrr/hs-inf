#pragma once
#include "Material.h"

class Wood : public Material {
public:
    Wood() {
        price = 500;
        name = "Holz";
    }
};
