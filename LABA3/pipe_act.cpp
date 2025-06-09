#include <iostream> 
#include "pipe_act.h" 
#include "pipe.h" 
#include "utils.h" 
#include <unordered_map>
#include <fstream>

using namespace std;

void addPipe(std::unordered_map<int, Pipe>& pipes) {
    Pipe pipe;
    cin >> pipe;
    pipes[pipe.get_id()] = pipe;
    cerr << "[LOG] Pipe added. ID = " << pipe.get_id() << "\n";
    cout << "Pipe added successfully.\n";
}

void viewPipes(const std::unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "No pipes available.\n";
    }
    else {
        for (const auto& [id, pipe] : pipes) {
            cout << pipe << endl;
        }
    }
}

void modifyPipeRepairStatus(std::unordered_map<int, Pipe>& pipes) {
    cout << "Enter pipe ID to modify: ";
    int pipeId = GetCorrectNumber<int>(1, Pipe::get_MaxID());

    auto it = pipes.find(pipeId);
    if (it != pipes.end()) {
        bool repairStatus = !it->second.get_repair();
        it->second.set_repair(repairStatus);
        cerr << "[LOG] Pipe ID = " << pipeId << " repair status changed to " << repairStatus << "\n";
        cout << "Pipe repair status updated.\n";
    }
    else {
        cerr << "[ERROR] Pipe ID = " << pipeId << " not found.\n";
        cout << "Pipe not found.\n";
    }
}

void deletePipe(std::unordered_map<int, Pipe>& pipes) {
    cout << "Enter pipe ID to delete: ";
    int pipeId = GetCorrectNumber<int>(1, Pipe::get_MaxID());

    if (pipes.erase(pipeId)) {
        cerr << "[LOG] Pipe ID = " << pipeId << " deleted.\n";
        cout << "Pipe deleted successfully.\n";
    }
    else {
        cerr << "[ERROR] Pipe ID = " << pipeId << " not found.\n";
        cout << "Pipe not found.\n";
    }
}
