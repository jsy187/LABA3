#pragma once 
#include <unordered_map> 
#include <unordered_set> 
#include "pipe.h" 


void modifyMultiplePipesRepairStatus(std::unordered_map<int, Pipe>& pipes);  // Новая функция для пакетного редактирования 


std::unordered_set<int> getPipesToModify(const std::unordered_map<int, Pipe>& pipes);
