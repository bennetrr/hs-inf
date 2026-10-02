#pragma once
#include <iostream>

class Material {
protected:
    int price;
    std::string name;
public:
    Material() {
        price = 0;
        name = "";
    }

    virtual ~Material() = default;

    virtual int getPrice() {
        return price;
    }

    virtual std::string getName() {
        return name;
    }
};
