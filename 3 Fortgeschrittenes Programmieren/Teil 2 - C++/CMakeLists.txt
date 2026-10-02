cmake_minimum_required(VERSION 3.29)
project(fprog_capycity)

set(CMAKE_CXX_STANDARD 20)

add_executable(fprog_capycity
        src/main.cpp
        src/Blueprint.cpp
        src/Blueprint.h
        src/buildings/Building.h
        src/buildings/HydroelectricFacility.h
        src/buildings/PhotovoltaicPark.h
        src/buildings/WindTurbine.h
        src/materials/Material.h
        src/materials/Metal.h
        src/materials/Plastics.h
        src/materials/Wood.h
        src/helpers.h
        src/helpers.cpp
        src/CapycitySim.cpp
        src/CapycitySim.h
)
