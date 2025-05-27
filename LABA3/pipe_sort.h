#pragma once 
#include <map> 
#include <unordered_map> 
#include "pipe.h" 

// Function declarations for sorting/filtering pipes 
void sortPipesByName(std::unordered_map<int, Pipe>& pipes);
void sortPipesByRepairStatus(std::unordered_map<int, Pipe>& pipes);
void filterPipesByName(std::unordered_map<int, Pipe>& pipes);
void filterPipesByRepairStatus(std::unordered_map<int, Pipe>& pipes);