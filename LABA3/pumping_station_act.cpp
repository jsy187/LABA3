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
    cerr << "[LOG] Pumping station added. ID = " << ps.get_id() << "\n";
    cout << "Pumping station added successfully.\n";
}

void viewPumpingStations(const std::unordered_map<int, PumpingStation>& pumpingStations) {
    if (pumpingStations.empty()) {
        cout << "No pumping stations available.\n";
    }
    else {
        for (const auto& [id, ps] : pumpingStations) {
            cout << ps << endl;
        }
    }
}

void modifyPumpingStationStatus(std::unordered_map<int, PumpingStation>& pumpingStations) {
    cout << "Enter pumping station ID to modify: ";
    int psId = GetCorrectNumber<int>(1, PumpingStation::get_MaxID());

    auto it = pumpingStations.find(psId);
    if (it != pumpingStations.end()) {
        PumpingStation& ps = it->second;

        cout << "1. Activate a shop\n"
            << "2. Deactivate a shop\n"
            << "Choose action: ";
        int action = GetCorrectNumber<int>(1, 2);

        if (action == 1) {
            if (ps.get_activeShops() < ps.get_totalShops()) {
                ps.set_activeShops(ps.get_activeShops() + 1);
                cerr << "[LOG] Activated 1 shop for station ID = " << psId << ". Now active: " << ps.get_activeShops() << "\n";
                cout << "One shop activated.\n";
            }
            else {
                cerr << "[INFO] All shops already active for station ID = " << psId << "\n";
                cout << "All shops are already active.\n";
            }
        }
        else {
            if (ps.get_activeShops() > 0) {
                ps.set_activeShops(ps.get_activeShops() - 1);
                cerr << "[LOG] Deactivated 1 shop for station ID = " << psId << ". Now active: " << ps.get_activeShops() << "\n";
                cout << "One shop deactivated.\n";
            }
            else {
                cerr << "[INFO] No active shops to deactivate for station ID = " << psId << "\n";
                cout << "No active shops to deactivate.\n";
            }
        }
    }
    else {
        cerr << "[ERROR] Pumping station ID = " << psId << " not found.\n";
        cout << "Pumping station not found.\n";
    }
}

void deletePumpingStation(std::unordered_map<int, PumpingStation>& pumpingStations) {
    cout << "Enter pumping station ID to delete: ";
    int psId = GetCorrectNumber<int>( 1, PumpingStation::get_MaxID());

    if (pumpingStations.erase(psId)) {
        cerr << "[LOG] Pumping station ID = " << psId << " deleted.\n";
        cout << "Pumping station deleted successfully.\n";
    }
    else {
        cerr << "[ERROR] Pumping station ID = " << psId << " not found.\n";
        cout << "Pumping station not found.\n";
    }
}