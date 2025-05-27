#include <iostream> 
#include <string> 
#include "pipe.h" 
#include "utils.h" 
#include <format>
#include <fstream>

using namespace std;

int Pipe::MaxID = 0;


int Pipe::get_MaxID() {
    return Pipe::MaxID;
}

int Pipe::get_id() const {
    return this->id;
}

string Pipe::get_name() const {
    return this->name;
}

double Pipe::get_length() const {
    return this->length;
}

int Pipe::get_diameter() const {
    return this->diameter;
}

bool Pipe::get_repair() const {
    return this->repair;
}

void Pipe::set_repair(bool new_repair) {
    this->repair = new_repair;
}

Pipe::Pipe() {
    name = "No name";
    diameter = 0;
    length = 0;
    repair = false;
}

ostream& operator << (ostream& out, const Pipe& pipe) {
    out << "Pipe id: " << pipe.id << endl
        << "Pipe name: " << pipe.name << endl
        << "Pipe diameter: " << pipe.diameter << endl
        << "Pipe length: " << pipe.length << endl
        << "Pipe repair: " << (pipe.repair ? "Yes" : "No") << endl;
    return out;
}


istream& operator >> (istream& in, Pipe& pipe) {
    pipe.id = ++pipe.MaxID;

    cout << "Pipe name > ";
    cin.ignore();
    getline(in, pipe.name);
    cout << "Pipe length > ";
    pipe.length = GetCorrectNumber<double>(1, 999);
    cout << "Pipe diameter > ";
    pipe.diameter = GetCorrectNumber<int>(1, 1400);
    cout << "Pipe repair > ";
    pipe.repair = GetCorrectNumber<bool>(0, 1);

    return in;
}

void Pipe::saveToFile(std::ofstream& file) const {
    file << id << "\n"
        << name << "\n"
        << length << "\n"
        << diameter << "\n"
        << repair << "\n";
}

void Pipe::loadFromFile(std::ifstream& file) {
    file >> id;
    file.ignore();
    std::getline(file, name);
    file >> length;
    file >> diameter;
    file >> repair;


    if (id > MaxID) {
        MaxID = id;
    }
}
