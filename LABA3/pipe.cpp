#include <iostream> 
#include <string> 
#include <fstream>

#include "utils.h"  
#include "pipe.h"

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


istream& operator>>(istream& in, Pipe& pipe) {
    cout << "Enter pipe name: ";
    INPUT_LINE(in, pipe.name);

    cout << "Enter pipe length: ";
    pipe.length = GetCorrectNumber<double>(0, 10000);

    cout << "Enter pipe diameter: ";
    pipe.diameter = GetCorrectNumber<int>( 100, 1400);

    cout << "Enter repair status (1 - in repair, 0 - working): ";
    pipe.repair = GetCorrectNumber<int>(0, 1);

    pipe.id = ++Pipe::MaxID;

    return in;
}

void Pipe::saveToFile(std::ofstream& file) const {
    file << id << "\n"
        << name << "\n"
        << length << "\n"
        << diameter << "\n"
        << repair << "\n";
}

void Pipe::loadFromFile(ifstream& file) {
    file >> id;
    file.ignore();
    getline(file, name);
    file >> length >> diameter >> repair;

    if (id > MaxID) {
        MaxID = id;
    }
}