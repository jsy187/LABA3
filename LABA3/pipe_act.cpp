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
    cout << "Pipe added successfully.\n";
}

void viewPipes(const std::unordered_map<int, Pipe>& pipes) {
    if (pipes.empty()) {
        cout << "No pipes available.\n";
    }
    else {
        for (const auto& p : pipes) {
            cout << p.second << endl;
        }
    }
}

void modifyPipeRepairStatus(std::unordered_map<int, Pipe>& pipes) {
    int pipeId;
    cout << "Enter pipe ID to modify: ";
    cin >> pipeId;
    if (pipes.find(pipeId) != pipes.end()) {
        bool repairStatus = !pipes[pipeId].get_repair();
        pipes[pipeId].set_repair(repairStatus);
        cout << "Pipe repair status updated.\n";
    }
    else {
        cout << "Pipe not found.\n";
    }
}

void deletePipe(std::unordered_map<int, Pipe>& pipes) {
    int pipeId;
    cout << "Enter pipe ID to delete: ";
    cin >> pipeId;
    if (pipes.find(pipeId) != pipes.end()) {
        pipes.erase(pipeId);
        cout << "Pipe deleted successfully.\n";
    }
    else {
        cout << "Pipe not found.\n";
    }
}
