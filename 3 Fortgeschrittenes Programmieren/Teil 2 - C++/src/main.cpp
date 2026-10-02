#include <iostream>
#include <string>

#include "Blueprint.h"
#include "CapycitySim.h"
#include "helpers.h"
#include "buildings/Building.h"
#include "buildings/HydroelectricFacility.h"
#include "buildings/PhotovoltaicPark.h"
#include "buildings/WindTurbine.h"

void action_new(CapycitySim& capycity_sim) {
    std::cout << "Namen des Plans eingeben: ";
    std::string name;
    std::cin >> name;

    std::cout << "Dimensionen eingeben (<dx>x<dy>): ";
    std::string dimStr;
    std::cin >> dimStr;
    int dim[2] = {0,0};
    splitStringToInts(dim, dimStr, 'x');

    if (dim[0] <= 0 || dim[1] <= 0) {
        std::cout << "Die Dimensionen müssen größer als 0 sein!" << std::endl;
    }

    capycity_sim.create_blueprint(name, dim[0], dim[1]);
}

void action_place(CapycitySim& capycity_sim) {
    std::cout << "Wa  Wasserkraftwerk" << std::endl;
    std::cout << "Wi  Windkraftwerk" << std::endl;
    std::cout << "So  Solarpanel" << std::endl;
    std::cout << "Gebäudetyp wählen (Wa|Wi|So) ";
    std::string artStr;
    std::cin >> artStr;

    std::cout << "Startposition eingeben (<x>,<y>) ";
    std::string posStr;
    std::cin >> posStr;
    int pos[2] = {0,0};
    splitStringToInts(pos, posStr, ',');

    std::cout << "Dimensionen eingeben (<dx>x<dy>) ";
    std::string dimStr;
    std::cin >> dimStr;
    int dim[2] = {0,0};
    splitStringToInts(dim, dimStr, 'x');

    try {
        if (artStr == "Wa") {
            capycity_sim.get_current_blueprint().set(new HydroelectricFacility(), pos[0], pos[1], dim[0], dim[1]);
        } else if (artStr == "Wi") {
            capycity_sim.get_current_blueprint().set(new WindTurbine(), pos[0], pos[1], dim[0], dim[1]);
        } else if (artStr == "So") {
            capycity_sim.get_current_blueprint().set(new PhotovoltaicPark(), pos[0], pos[1], dim[0], dim[1]);
        } else {
            std::cout << "Unbekannter Gebäudetyp!" << std::endl;
        }
    } catch (std::overflow_error&) {
        std::cout << "In dem gewählten Baubereich ist schon ein Gebäude platziert!" << std::endl;
    } catch (std::out_of_range&) {
        std::cout << "Der angegebene Bereich liegt außerhalb des Plans!" << std::endl;
    }
}

void action_clear(CapycitySim& capycity_sim) {
    std::cout << "Startposition eingeben (<x>,<y>) ";
    std::string posStr;
    std::cin >> posStr;
    int pos[2] = {0,0};
    splitStringToInts(pos, posStr, ',');

    std::cout << "Dimensionen eingeben (<dx>x<dy>) ";
    std::string dimStr;
    std::cin >> dimStr;
    int dim[2] = {0,0};
    splitStringToInts(dim, dimStr, 'x');

    try {
        capycity_sim.get_current_blueprint().set(nullptr, pos[0], pos[1], dim[0], dim[1]);
    } catch (std::out_of_range&) {
        std::cout << "Der angegebene Bereich liegt außerhalb des Plans!" << std::endl;
    }
}

int main() {
    CapycitySim capycity_sim = CapycitySim();

    while (true) {
        bool new_capycity_sim = capycity_sim.is_empty();

        if (new_capycity_sim) {
            std::cout << std::endl;
            std::cout << "Willkommen zum CapycitySim" << std::endl;
            std::cout << "N  Neuen Bauplan erstellen" << std::endl;
            std::cout << "O  Alle Baupläne ausgeben" << std::endl;
            std::cout << "B  Programm beenden" << std::endl;
            std::cout << "Menüpunkt wählen (N|O|B): ";
        } else {
            std::cout << std::endl;
            std::cout << "Hauptmenü" << std::endl;
            std::cout << "N  Neuen Bauplan erstellen" << std::endl;
            std::cout << "P  Gebäude platzieren" << std::endl;
            std::cout << "L  Bereich löschen" << std::endl;
            std::cout << "A  Aktuellen Bauplan ausgeben" << std::endl;
            std::cout << "O  Alle Baupläne ausgeben" << std::endl;
            std::cout << "B  Programm beenden" << std::endl;
            std::cout << "Menüpunkt wählen (N|P|L|A|O|B): ";
        }

        char choice;
        std::cin >> choice;
        std::cout << std::endl;

        if (choice == 'N' || choice == 'n') {
            action_new(capycity_sim);
        } else if (!new_capycity_sim && (choice == 'P' || choice == 'p')) {
            action_place(capycity_sim);
        } else if (!new_capycity_sim && (choice == 'L' || choice == 'l')) {
            action_clear(capycity_sim);
        } else if (!new_capycity_sim && (choice == 'A' || choice == 'a')) {
            std::cout << capycity_sim.get_current_blueprint();
        } else if (choice == 'O' || choice == 'o') {
            std::cout << capycity_sim;
        } else if (choice == 'B' || choice == 'b') {
            return EXIT_SUCCESS;
        } else std::cout << "Unbekannte option" << std::endl;
    }
}
