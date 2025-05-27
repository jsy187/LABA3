#pragma once 

#include <string> 
#include <iostream> 

class PumpingStation {
private:
    int id;
    static int MaxID;
    std::string name;
    int totalShops;
    int activeShops;
    double efficiency;

public:
    PumpingStation();
    static int get_MaxID();
    int get_id() const;
    std::string get_name() const;
    int get_totalShops() const;
    int get_activeShops() const;
    double get_efficiency() const;

    void set_activeShops(int new_activeShops);
    void set_efficiency(double new_efficiency);

    friend std::ostream& operator << (std::ostream& out, const PumpingStation& stations);
    friend std::istream& operator >> (std::istream& in, PumpingStation& stations);
    void saveToFile(std::ofstream& file) const;
    void loadFromFile(std::ifstream& file);
};

