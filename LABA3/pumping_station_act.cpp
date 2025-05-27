#include <iostream> 
#include "pumping_station_act.h" 
#include "pumping_station.h" 
#include "utils.h" 
#include "graph.h"

using namespace std;

void addPumpingStation(std::unordered_map<int, PumpingStation>& pumpingStations) {
    PumpingStation ps;
    cin >> ps;
    pumpingStations[ps.get_id()] = ps;
    cout << "Pumping station added successfully.\n";
}

void viewPumpingStations(const std::unordered_map<int, PumpingStation>& pumpingStations) {
    if (pumpingStations.empty()) {
        cout << "No pumping stations available.\n";
    }
    else {
        for (const auto& ps : pumpingStations) {
            cout << ps.second << endl;
        }
    }
}

void modifyPumpingStationStatus(std::unordered_map<int, PumpingStation>& pumpingStations) {
    int psId;
    cout << "Enter pumping station ID to modify: ";
    cin >> psId;
    if (pumpingStations.find(psId) != pumpingStations.end()) {
        PumpingStation& ps = pumpingStations[psId];
        int action;
        cout << "1. Activate a shop\n"
            << "2. Deactivate a shop\n"
            << "Choose action: ";
        action = GetCorrectNumber<int>(1, 2);

        if (action == 1) {
            if (ps.get_activeShops() < ps.get_totalShops()) {
                ps.get_activeShops() + 1;
                cout << "One shop activated.\n";
            }
            else {
                cout << "All shops are already active.\n";
            }
        }
        else if (action == 2) {
            if (ps.get_activeShops() > 0) {
                ps.get_activeShops() - 1;
                cout << "One shop deactivated.\n";
            }
            else {
                cout << "No active shops to deactivate.\n";
            }
        }
    }
    else {
        cout << "Pumping station not found.\n";
    }
}

void deletePumpingStation(std::unordered_map<int, PumpingStation>& pumpingStations) {
    int psId;
    cout << "Enter pumping station ID to delete: ";
    cin >> psId;

    if (pumpingStations.find(psId) != pumpingStations.end()) {
        pumpingStations.erase(psId);
        cout << "Pumping station deleted successfully.\n";
    }
    else {
        cout << "Pumping station not found.\n";
    }
}