#include "Blueprint.h"
#include "buildings/HydroelectricFacility.h"
#include "buildings/PhotovoltaicPark.h"
#include "buildings/WindTurbine.h"

Blueprint::Blueprint(std::string name, int dx, int dy) : name(std::move(name)), dx(dx), dy(dy) {
    this->arr = new Building*[dx * dy] { nullptr };
}

Blueprint::Blueprint(const Blueprint& other) : name(other.name), dx(other.dx), dy(other.dy) {
    this->arr = new Building*[dx * dy];
    memcpy(this->arr, other.arr, sizeof(Building*) * dx * dy);
}

Blueprint::~Blueprint() {
    delete[] this->arr;
}

std::string Blueprint::get_name() {
    return this->name;
}

int Blueprint::get_dx() {
    return this->dx;
}

int Blueprint::get_dy() {
    return this->dy;
}

double Blueprint::get_key_metric() {
    int capacity = 0;
    int price = 0;

    for (int i = 0; i < this->dx * this->dy; i++) {
        if (this->arr[i] != nullptr) {
            capacity += this->arr[i]->get_capacity();
            price += this->arr[i]->get_price();
        }
    }

    if (price == 0) {
        return 0;
    }

    return static_cast<double>(capacity) / (price * this->dx * this->dy);
}

Building* Blueprint::at(int& x, int& y) {
    if (x < 0 || y < 0 || x >= this->dx || y >= this->dy) {
        throw std::out_of_range("Baubereich::get");
    }

    return this->arr[y * this->dx + x];
}

void Blueprint::set(Building *value, int &x, int &y, int &dx, int &dy) {
    if (x < 0 || y < 0 || x + dx - 1 >= this->dx || y + dy - 1 >= this->dy) {
        throw std::out_of_range("Baubereich::set");
    }

    if (value != nullptr) {
        // Check if the area conflicts with other buildings
        for (int _x = x; _x < x + dx; _x++) {
            for (int _y = y; _y < y + dy; _y++) {
                if (this->at(_x, _y) != nullptr) {
                    throw std::overflow_error("Baubereich::set");
                }
            }
        }
    }

    for (int _x = x; _x < x + dx; _x++) {
        for (int _y = y; _y < y + dy; _y++) {
            this->arr[_y * this->dx + _x] = value;
        }
    }
}

bool Blueprint::operator()(Blueprint& other) {
    if (this->get_dx() != other.get_dx() || this->get_dy() != other.get_dy()) {
        return false;
    }

    for (int x = 0; x < this->get_dx(); ++x) {
        for (int y = 0; y < this->get_dy(); ++y) {
            if (typeid(this->at(x, y)) != typeid(other.at(x, y))) {
                return false;
            }
        }
    }

    return true;
}

void output_building_count(int count, const std::string& label) {
    Building* building;

    if (label == "Wa") building = new HydroelectricFacility();
    else if (label == "Wi") building = new WindTurbine();
    else if (label == "So") building = new PhotovoltaicPark();
    else throw std::invalid_argument("Unkown building type");

    Material metal = Metal();
    Material plastics = Plastics();
    Material wood = Wood();

    printf("%d x %s (%d x Holz, %d x Metall, %d x Kunst) = %d Capydollar\n",
        count,
        building->get_label().c_str(),
        count * building->get_materials()->at(std::type_index(typeid(Wood))),
        count * building->get_materials()->at(std::type_index(typeid(Metal))),
        count * building->get_materials()->at(std::type_index(typeid(Plastics))),
        count * building->get_price()
    );

    delete building;
}

std::ostream& operator<<(std::ostream& os, Blueprint& blueprint) {
    os << "Bauplan \"" << blueprint.get_name() << "\" (" << blueprint.get_dx() << "x" << blueprint.get_dy() << ")" << std::endl;

    int count_wa = 0, count_wi = 0, count_so = 0;
    std::string row_seperator(blueprint.get_dx() * 5 + 3, '-');

    // Top left corner of the table
    if (blueprint.get_dy() <= 9) {
        os << "  |";
    } else {
        os << "   |";
    }

    // Row header
    for (int x = 0; x < blueprint.get_dx(); x++) {
        if (x <= 9) {
            os << " " << x << "  |";
        } else {
            os << " " << x << " |";
        }
    }
    os << std::endl;

    // For every row
    for (int y = 0; y < blueprint.get_dy(); y++) {
        os << row_seperator << std::endl;
        // Column header
        os << y << " |";

        // For every column
        for (int x = 0; x < blueprint.get_dx(); x++) {
            Building* cell = blueprint.at(x,y);

            if (cell == nullptr) {
                os << "    |";
                continue;
            }

            os << " " << cell->get_label() << " |";

            if (cell->get_label() == "Wa") count_wa++;
            else if (cell->get_label() == "Wi") count_wi++;
            else if (cell->get_label() == "So") count_so++;
        }
        os << std::endl;
    }

    os << std::endl;
    output_building_count(count_wa, "Wa");
    output_building_count(count_wi, "Wi");
    output_building_count(count_so, "So");
    os << "Kennzahl: " << blueprint.get_key_metric() << std::endl;

    os << std::endl;
    return os;
}
