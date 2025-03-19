#include <iostream>
#include "CelestialEntity.h"
#include "Sun.h"
#include "Planet.h"
#include "SolarSpace.h"
#include <chrono>
#include <thread>
#include <vector>
void update(std::vector<CelestialEntity*>& entities) 
{
	for (auto entity : entities) {
		entity->increaseTemperature();
		if (entity->checkTemperature()) {
			delete entity;
			entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		}
	}
	
}
int main()
{
	const double timestep = 0.1;
	int positions[2] = {-12,10};
	SolarSpace space(31, 31);

	Sun* newsun= new Sun(3, positions, 0, 900, "yellow", "Marinica");
	space.addSun(positions, newsun->getSize());

	space.display();
	Planet* newplanet = new Planet(1, positions, 0, true, "Earth", 4);
	Planet* newplanet2 = new Planet(2, positions, 0, true, "Mars", 10);
	Planet* newplanet3 = new Planet(2, positions, 0, true, "Venus", 30);
    std::vector<CelestialEntity*> entities;
	entities.push_back(newsun);
	entities.push_back(newplanet);
	entities.push_back(newplanet2);
	entities.push_back(newplanet3);
	while (!entities.empty()) {
        auto start = std::chrono::high_resolution_clock::now();

        update(entities);

        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double sleepTime = timestep - elapsed.count();

        if (sleepTime > 0) {
            std::this_thread::sleep_for(std::chrono::duration<double>(sleepTime));
        }
    }

	return 0;
}