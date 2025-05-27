#include "pipes_act.h" 
#include <iostream> 
#include <unordered_set> 

// ������� ��� ��������� ������ ID ����, ������� ������������ ����� ��������������� 
std::unordered_set<int> getPipesToModify(const std::unordered_map<int, Pipe>& pipes) {
    std::unordered_set<int> pipesToModify;
    int choice;
    std::cout << "Do you want to modify all pipes? (1 - Yes, 0 - No): ";
    std::cin >> choice;
    if (choice == 1) {
        // ���� ������� ����� ������������� ��� ����� 
        for (const auto& pipe : pipes) {
            pipesToModify.insert(pipe.first);  // ��������� ��� ID ���� 
        }
    }
    else {
        // ���� ������� ����� ������������� ��������� ����� 
        std::cout << "Enter Pipe IDs to modify (enter 0 to stop): " << std::endl;
        while (true) {
            int id;
            std::cout << "Enter Pipe ID: ";
            std::cin >> id;
            if (id == 0) break;  // ����� �� ����� 
            if (pipes.find(id) != pipes.end()) {
                pipesToModify.insert(id);  // ��������� ID ����� � ������ 
            }
            else {
                std::cout << "Pipe with ID " << id << " not found." << std::endl;
            }
        }
    }
    return pipesToModify;
}

// ������� ��� �������������� ������� ������� ���������� ���� 
void modifyMultiplePipesRepairStatus(std::unordered_map<int, Pipe>& pipes) {
    std::unordered_set<int> pipesToModify = getPipesToModify(pipes);

    if (pipesToModify.empty()) {
        std::cout << "No pipes selected for modification." << std::endl;
        return;
    }

    bool newRepairStatus;
    std::cout << "Enter new repair status (1 for repaired, 0 for not): ";
    std::cin >> newRepairStatus;

    for (int id : pipesToModify) {
        pipes[id].set_repair(newRepairStatus);  // ��������� ������ ������� ��� ��������� ���� 
    }

    std::cout << "Repair status updated for selected pipes." << std::endl;
}
