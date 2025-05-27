#include <iostream> 
#include <map> 
#include "pumping_station_sort.h" 
#include "pumping_station.h" 

using namespace std;

// Sort pumping stations by name 
void sortPumpingStationsByName(std::unordered_map<int, PumpingStation>& stations) {
    map<string, PumpingStation> sortedStations;

    // Populate the map with pumping station name as the key 
    for (const auto& stationPair : stations) {
        sortedStations[stationPair.second.get_name()] = stationPair.second;
    }

    cout << "Pumping Stations sorted by name:\n";
    for (const auto& station : sortedStations) {
        cout << station.second << endl;
    }
}

// Sort pumping stations by percentage of inactive shops 
void sortPumpingStationsByInactiveShopsPercentage(std::unordered_map<int, PumpingStation>& stations) {
    map<double, PumpingStation> sortedStations;

    // Populate the map with inactive shop percentage as the key 
    for (const auto& stationPair : stations) {
        double inactivePercentage = 100.0 * (stationPair.second.get_totalShops() - stationPair.second.get_activeShops()) / stationPair.second.get_totalShops();
        sortedStations[inactivePercentage] = stationPair.second;
    }

    cout << "Pumping Stations sorted by percentage of inactive shops:\n";
    for (const auto& station : sortedStations) {
        cout << station.second << endl;
    }
}

// Filter pumping stations by name 
void filterPumpingStationsByName(std::unordered_map<int, PumpingStation>& stations) {
    string filterName;
    cout << "Enter name to filter pumping stations: ";
    cin.ignore();
    getline(cin, filterName);

    bool found = false;
    for (const auto& stationPair : stations) {
        if (stationPair.second.get_name() == filterName) {
            cout << stationPair.second << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No pumping stations found with that name.\n";
    }
}

// Filter pumping stations by percentage of inactive shops 
void filterPumpingStationsByInactiveShopsPercentage(std::unordered_map<int, PumpingStation>& stations) {
    double filterPercentage;
    cout << "Enter the percentage of inactive shops to filter pumping stations: ";
    cin >> filterPercentage;

    bool found = false;
    for (const auto& stationPair : stations) {
        double inactivePercentage = 100.0 * (stationPair.second.get_totalShops() - stationPair.second.get_activeShops()) / stationPair.second.get_totalShops();
        if (inactivePercentage >= filterPercentage) {
            cout << stationPair.second << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No pumping stations found with that inactive shop percentage.\n";
    }
}