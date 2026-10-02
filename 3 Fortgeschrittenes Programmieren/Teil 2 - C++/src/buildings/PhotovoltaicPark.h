#pragma once
#include <string>

#include "../materials/Material.h"
#include "../materials/Metal.h"
#include "../materials/Plastics.h"

class PhotovoltaicPark : public Building {
public:
    PhotovoltaicPark() {
        base_price = 18000;
        label = "So";
        materials = new std::unordered_map<std::type_index, int> {
            {std::type_index(typeid(Metal)), 6},
            {std::type_index(typeid(Plastics)), 3},
            {std::type_index(typeid(Wood)), 0}
        };
        capacity = 5000;
    }
};
