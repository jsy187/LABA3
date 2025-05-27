#include "pipes_act.h" 
#include <iostream> 
#include <unordered_set> 

// Функция для получения списка ID труб, которые пользователь хочет отредактировать 
std::unordered_set<int> getPipesToModify(const std::unordered_map<int, Pipe>& pipes) {
    std::unordered_set<int> pipesToModify;
    int choice;
    std::cout << "Do you want to modify all pipes? (1 - Yes, 0 - No): ";
    std::cin >> choice;
    if (choice == 1) {
        // Если выбрана опция редактировать все трубы 
        for (const auto& pipe : pipes) {
            pipesToModify.insert(pipe.first);  // Добавляем все ID труб 
        }
    }
    else {
        // Если выбрана опция редактировать выбранные трубы 
        std::cout << "Enter Pipe IDs to modify (enter 0 to stop): " << std::endl;
        while (true) {
            int id;
            std::cout << "Enter Pipe ID: ";
            std::cin >> id;
            if (id == 0) break;  // Выход из ввода 
            if (pipes.find(id) != pipes.end()) {
                pipesToModify.insert(id);  // Добавляем ID трубы в список 
            }
            else {
                std::cout << "Pipe with ID " << id << " not found." << std::endl;
            }
        }
    }
    return pipesToModify;
}

// Функция для редактирования статуса ремонта нескольких труб 
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
        pipes[id].set_repair(newRepairStatus);  // Обновляем статус ремонта для выбранных труб 
    }

    std::cout << "Repair status updated for selected pipes." << std::endl;
}
