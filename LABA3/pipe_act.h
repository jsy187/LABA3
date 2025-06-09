#pragma once
#include "pipe.h"
#include <unordered_map>

void addPipe(std::unordered_map<int, Pipe>& pipes);
void viewPipes(const std::unordered_map<int, Pipe>& pipes);
void modifyPipeRepairStatus(std::unordered_map<int, Pipe>& pipes);
void deletePipe(std::unordered_map<int, Pipe>& pipes);
