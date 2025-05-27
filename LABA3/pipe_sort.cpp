#include <iostream> 
#include <map> 
#include "pipe_sort.h" 
#include "pipe.h" 

using namespace std;

void sortPipesByName(std::unordered_map<int, Pipe>& pipes) {
    map<string, Pipe> sortedPipes;

    for (const auto& pipePair : pipes) {
        sortedPipes[pipePair.second.get_name()] = pipePair.second;
    }

    cout << "Pipes sorted by name:\n";
    for (const auto& pipe : sortedPipes) {
        cout << pipe.second << endl;
    }
}

void sortPipesByRepairStatus(std::unordered_map<int, Pipe>& pipes) {
    map<bool, Pipe> sortedPipes;

    // Populate the map with repair status as the key 
    for (const auto& pipePair : pipes) {
        sortedPipes[pipePair.second.get_repair()] = pipePair.second;
    }

    cout << "Pipes sorted by repair status (0 = not repaired, 1 = repaired):\n";
    for (const auto& pipe : sortedPipes) {
        cout << pipe.second << endl;
    }
}

void filterPipesByName(std::unordered_map<int, Pipe>& pipes) {
    string filterName;
    cout << "Enter name to filter pipes: ";
    cin.ignore();
    getline(cin, filterName);

    bool found = false;
    for (const auto& pipePair : pipes) {
        if (pipePair.second.get_name() == filterName) {
            cout << pipePair.second << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No pipes found with that name.\n";
    }
}

void filterPipesByRepairStatus(std::unordered_map<int, Pipe>& pipes) {
    bool repairStatus;
    cout << "Enter repair status to filter pipes (0 = not repaired, 1 = repaired): ";
    cin >> repairStatus;

    bool found = false;
    for (const auto& pipePair : pipes) {
        if (pipePair.second.get_repair() == repairStatus) {
            cout << pipePair.second << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No pipes found with that repair status.\n";
    }
}