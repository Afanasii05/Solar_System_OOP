#pragma once
#include <string>
#include "CelestialEntity.h"
#include <SFML/Graphics.hpp>

// Forward declaration of SolarSpace
class SolarSpace;

class Planet : public CelestialEntity
{
private:
    bool habitable;
    std::string name;
    float temperature = 0;
    int orbitingSun = 0;

    float density = 10200;

public:
    Planet(float size, bool habitable, std::string name,int orbitingSun);
    bool checkTemperature() override;
    float getTemperature() const { return temperature; }
    void setTemperature(float temperature);
    std::string getName() { return name; }
    float getMass() override { return size * density; }
    int getOrbitingSunIndex() const{ return orbitingSun; }
    ~Planet();
};