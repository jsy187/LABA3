#pragma once 
#include "pumping_station.h" 
#include <unordered_map> 

 
void addPumpingStation(std::unordered_map<int, PumpingStation>& pumpingStations);
void viewPumpingStations(const std::unordered_map<int, PumpingStation>& pumpingStations);
void modifyPumpingStationStatus(std::unordered_map<int, PumpingStation>& pumpingStations);
void deletePumpingStation(std::unordered_map<int, PumpingStation>& pumpingStations);
