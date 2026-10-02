#pragma once
#include <string>

#include "../materials/Material.h"
#include "../materials/Metal.h"
#include "../materials/Plastics.h"
#include "../materials/Wood.h"

class WindTurbine : public Building {
public:
    WindTurbine() {
        base_price = 20000;
        label = "Wi";
        materials = new std::unordered_map<std::type_index, int> {
            {std::type_index(typeid(Metal)), 2},
            {std::type_index(typeid(Plastics)), 5},
            {std::type_index(typeid(Wood)), 2}
        };
        capacity = 4500;
    }
};
