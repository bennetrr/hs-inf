#pragma once
#include <string>

#include "../materials/Metal.h"
#include "../materials/Plastics.h"
#include "../materials/Wood.h"

class HydroelectricFacility : public Building {
public:
    HydroelectricFacility() {
        base_price = 25000;
        label = "Wa";
        materials = new std::unordered_map<std::type_index, int> {
            {std::type_index(typeid(Metal)), 3},
            {std::type_index(typeid(Plastics)), 1},
            {std::type_index(typeid(Wood)), 5}
        };
        capacity = 3000;
    }
};
