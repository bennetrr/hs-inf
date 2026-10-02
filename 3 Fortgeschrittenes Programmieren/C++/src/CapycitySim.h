#pragma once
#include <vector>

#include "Blueprint.h"

class CapycitySim {
private:
    std::vector<Blueprint> blueprints;
    Blueprint* current_blueprint;
public:
    CapycitySim();

    void create_blueprint(std::string name, int dx, int dy);

    Blueprint& get_current_blueprint();

    std::vector<Blueprint> get_all_blueprints();

    bool is_empty();
};

std::ostream& operator<<(std::ostream& os, CapycitySim& capycity_sim);
