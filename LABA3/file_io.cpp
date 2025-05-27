#include <iostream>
#include <fstream>
#include <unordered_map>
#include "pipe.h"
#include "pumping_station.h"
#include "utils.h"
#include "file_io.h"
#include "graph.h"

using namespace std;


void loadDataFromFile(unordered_map<int, Pipe>& pipes, unordered_map<int, PumpingStation>& stations, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for reading.\n";
        return;
    }

    string type;
    while (file >> type) {
        if (type == "Pipe") {
            Pipe pipe;
            pipe.loadFromFile(file);
            pipes[pipe.get_id()] = pipe;
        }
        else if (type == "PumpingStation") {
            PumpingStation ps;
            ps.loadFromFile(file);
            stations[ps.get_id()] = ps;
        }
    }

    file.close();
    cout << "Data loaded from file successfully.\n";
}


void saveDataToFile(const unordered_map<int, Pipe>& pipes, const unordered_map<int, PumpingStation>& stations, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open file for writing.\n";
        return;
    }

    for (const auto& pipe : pipes) {
        file << "Pipe\n";
        pipe.second.saveToFile(file);
    }

    for (const auto& station : stations) {
        file << "PumpingStation\n";
        station.second.saveToFile(file);
    }

    file.close();
    cout << "Data saved to file successfully.\n";
}

void saveGraphToFile(const std::unordered_map<int, std::vector<Connection>>& graph,
    const std::string& filename) {
    std::ofstream file(filename + "graph");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for writing.\n";
        return;
    }

    for (const auto& node : graph) {
        for (const auto& connection : node.second) {
            file << connection.id << "\n"
                << connection.pipeId << "\n"
                << connection.sourceId << "\n"
                << connection.targetId << "\n";
        }
    }

    file.close();
    std::cout << "Graph saved to file successfully.\n";
}


void loadGraphFromFile(std::unordered_map<int, std::vector<Connection>>& graph,
    const std::string& filename) {
    std::ifstream file(filename + "graph");
    if (!file.is_open()) {
        std::cerr << "Failed to open file for reading.\n";
        return;
    }

    Connection connection;
    while (file >> connection.id >> connection.pipeId >> connection.sourceId >> connection.targetId) {
        graph[connection.sourceId].push_back(connection);
    }

    file.close();
    std::cout << "Graph loaded from file successfully.\n";
}
