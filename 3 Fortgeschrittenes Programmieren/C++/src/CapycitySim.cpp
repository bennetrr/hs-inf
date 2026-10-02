#include "CapycitySim.h"

CapycitySim::CapycitySim() {
    this->blueprints = std::vector<Blueprint>();
    this->current_blueprint = nullptr;
}

void CapycitySim::create_blueprint(std::string name, int dx, int dy) {
    // If the CapycitySim was already initialized, save the previous blueprint into the vector
    if (this->current_blueprint != nullptr) {
        // Only save if there isn't already an equal blueprint
        if (std::ranges::none_of(this->blueprints, *this->current_blueprint)) {
            this->blueprints.emplace_back(*this->current_blueprint);
        }
    }

    this->current_blueprint = new Blueprint(std::move(name), dx, dy);
}

Blueprint& CapycitySim::get_current_blueprint() {
    if (this->current_blueprint == nullptr) {
        throw std::out_of_range("No blueprints found");
    }

    return *this->current_blueprint;
}

std::vector<Blueprint> CapycitySim::get_all_blueprints() {
    return this->blueprints;
}

bool CapycitySim::is_empty() {
    return this->current_blueprint == nullptr;
}

std::ostream &operator<<(std::ostream &os, CapycitySim &capycity_sim) {
    if (capycity_sim.is_empty()) {
        os << "Keine Baupläne vorhanden!" << std::endl;
        return os;
    }

    os << "Aktueller " << capycity_sim.get_current_blueprint();

    for (Blueprint &blueprint: capycity_sim.get_all_blueprints()) {
        os << blueprint;
    }

    return os;
}
