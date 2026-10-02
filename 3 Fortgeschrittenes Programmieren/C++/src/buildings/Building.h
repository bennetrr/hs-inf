#pragma once
#include <string>
#include <typeindex>

#include "../materials/Material.h"
#include "../materials/Metal.h"
#include "../materials/Plastics.h"
#include "../materials/Wood.h"

class Building {
protected:
    int base_price;
    std::string label;
    std::unordered_map<std::type_index, int> *materials;
    int capacity;

public:
    Building() {
        base_price = 0;
        label = "";
        materials = nullptr;
        capacity = 0;
    }

    virtual ~Building() = default;

    virtual int get_price() {
        return base_price +
            materials->at(std::type_index(typeid(Metal))) * Metal().getPrice() +
            materials->at(std::type_index(typeid(Plastics))) * Plastics().getPrice() +
            materials->at(std::type_index(typeid(Wood))) * Wood().getPrice();
    }

    virtual std::string get_label() { return label; }

    virtual std::unordered_map<std::type_index, int> *get_materials() { return materials; }

    virtual int get_capacity() { return capacity; }
};
