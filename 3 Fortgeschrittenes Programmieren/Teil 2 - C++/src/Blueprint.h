#pragma once
#include "buildings/Building.h"

class Blueprint {
private:
    std::string name;
    int dx;
    int dy;
    Building** arr;
public:
    Blueprint(std::string name, int dx, int dy);

    Blueprint(const Blueprint& other);

    ~Blueprint();

    std::string get_name();

    int get_dx();

    int get_dy();

    double get_key_metric();

    Building* at(int& x, int& y);

    void set(Building* value, int& x, int& y, int& dx, int& dy);

    bool operator()(Blueprint& other);
};

std::ostream& operator<<(std::ostream& os, Blueprint& blueprint);
