#include <iostream>
#include "CelestialEntity.h"
#include "Sun.h"
#include "Planet.h"
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
	float positions[2] = {0,0};
	Sun* newsun= new Sun(10, positions, 0, 900, "yellow", "Marinica");
	Planet* newplanet = new Planet(5, positions, 0, true, "Earth", (int)(newsun->getTemperature()*0.1),44);
	Planet* newplanet2 = new Planet(5, positions, 0, true, "Mars", (int)(newsun->getTemperature() * 0.2), 100);
	Planet* newplanet3 = new Planet(5, positions, 0, true, "Venus", (int)(newsun->getTemperature() * 0.01), 30);
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