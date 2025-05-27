#pragma once 
#include <map> 
#include <unordered_map> 
#include "pumping_station.h" 

// Function declarations for sorting/filtering pumping stations 
void sortPumpingStationsByName(std::unordered_map<int, PumpingStation>& stations);
void sortPumpingStationsByInactiveShopsPercentage(std::unordered_map<int, PumpingStation>& stations);
void filterPumpingStationsByName(std::unordered_map<int, PumpingStation>& stations);
void filterPumpingStationsByInactiveShopsPercentage(std::unordered_map<int, PumpingStation>& stations);