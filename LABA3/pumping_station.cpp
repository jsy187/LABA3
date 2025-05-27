#include <iostream> 
#include <string> 
#include "pumping_station.h" 
#include "utils.h" 
#include <fstream>

using namespace std;

int PumpingStation::MaxID = 0;

int PumpingStation::get_MaxID() {
    return PumpingStation::MaxID;
}

int PumpingStation::get_id() const {
    return this->id;
}


std::string PumpingStation::get_name() const {
    return this->name;
}

int PumpingStation::get_totalShops() const {
    return this->totalShops;
}

int PumpingStation::get_activeShops() const {
    return this->activeShops;
}

double PumpingStation::get_efficiency() const {
    return this->efficiency;
}

void PumpingStation::set_activeShops(int new_activeShops) {
    this->activeShops = new_activeShops;
}

void PumpingStation::set_efficiency(double new_efficiency) {
    this->efficiency = new_efficiency;
}

PumpingStation::PumpingStation() {
    name = "No Name";
    totalShops = 0;
    activeShops = 0;
    efficiency = 0.0;
}

ostream& operator << (ostream& out, const PumpingStation& ps) {
    out << "Pumping Station id: " << ps.id << endl
        << "Pumping Station name: " << ps.name << endl
        << "Total Shops: " << ps.totalShops << endl
        << "Active Shops: " << ps.activeShops << endl
        << "Efficiency: " << ps.efficiency << endl;
    return out;
}

istream& operator >> (istream& in, PumpingStation& ps) {
    ps.id = ++ps.MaxID;
    cout << "Pumping Station name > ";
    cin.ignore();
    getline(in, ps.name);
    cout << "Total shops > ";
    ps.totalShops = GetCorrectNumber<int>(1, 100);
    cout << "Active shops > ";
    ps.activeShops = GetCorrectNumber<int>(0, ps.totalShops);
    cout << "Efficiency > ";
    ps.efficiency = GetCorrectNumber<double>(0.0, 100.0);

    return in;
}
void PumpingStation::saveToFile(std::ofstream& file) const {
    file << id << "\n"
        << name << "\n"
        << totalShops << "\n"
        << activeShops << "\n"
        << efficiency << "\n";
}

void PumpingStation::loadFromFile(std::ifstream& file) {
    file >> id;
    file.ignore();
    std::getline(file, name);
    file >> totalShops;
    file >> activeShops;
    file >> efficiency;


    if (id > MaxID) {
        MaxID = id;
    }
}