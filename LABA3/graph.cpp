#include "graph.h"
#include <iostream>
#include "pipe_act.h"

void connectStations(std::unordered_map<int, Pipe>& pipes,
    std::unordered_map<int, PumpingStation>& stations,
    std::unordered_map<int, std::vector<Connection>>& graph) {
    int sourceId, targetId, diameter;
    std::cout << "Enter source station ID: ";
    std::cin >> sourceId;
    std::cout << "Enter target station ID: ";
    std::cin >> targetId;
    std::cout << "Enter pipe diameter (500, 700, 1000, 1400): ";
    std::cin >> diameter;


    if (stations.find(sourceId) == stations.end() || stations.find(targetId) == stations.end()) {
        std::cout << "Error: One or both stations do not exist.\n";
        return;
    }


    if (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
        std::cerr << "Error: Invalid diameter. Allowed values: 500, 700, 1000, 1400.\n";
        return;
    }


    int pipeId = -1;
    for (const auto& pipe : pipes) {
        if (pipe.second.get_diameter() == diameter && !pipe.second.get_repair()) {
            bool isPipeUsed = false;
            for (const auto& connections : graph) {
                for (const auto& connection : connections.second) {
                    if (connection.pipeId == pipe.first) {
                        isPipeUsed = true;
                        break;
                    }
                }
                if (isPipeUsed) break;
            }
            if (!isPipeUsed) {
                pipeId = pipe.first;
                break;
            }
        }
    }

    if (pipeId == -1) {
        std::cout << "No available pipe with diameter " << diameter << ". Create a new pipe.\n";
        addPipe(pipes);
        pipeId = Pipe::get_MaxID();
    }

    Connection connection;
    connection.id = graph.size() + 1;
    connection.pipeId = pipeId;
    connection.sourceId = sourceId;
    connection.targetId = targetId;


    graph[sourceId].push_back(connection);

    std::cout << "Stations connected successfully.\n";
}

void removeEdge(std::unordered_map<int, std::vector<Connection>>& graph,
    std::unordered_map<int, PumpingStation>& stations, int stid) {
    if (stations.find(stid) == stations.end()) {
        std::cerr << "Wrong id, NO pump station" << std::endl;
    }
    stations.erase(stid);
    for (auto& [sourceId, connections] : graph) {
        connections.erase(std::remove_if(connections.begin(), connections.end(), [stid](const Connection& con) {
            return con.sourceId == stid || con.targetId == stid;
            }),
            connections.end()
        );
    }
    graph.erase(stid);
    std::cout << "Delete station id: " << stid << std::endl;

}

void topologicalSortUtil(int stationId,
    std::unordered_map<int, std::vector<Connection>>& graph,
    std::unordered_set<int>& visited,
    std::unordered_set<int>& recStack,
    std::stack<int>& stack,
    bool& hasCycle) {
    if (hasCycle) return;

    visited.insert(stationId);
    recStack.insert(stationId);

    for (const auto& connection : graph[stationId]) {
        if (recStack.find(connection.targetId) != recStack.end()) {
            hasCycle = true;
            return;
        }
        if (visited.find(connection.targetId) == visited.end()) {
            topologicalSortUtil(connection.targetId, graph, visited, recStack, stack, hasCycle);
        }
    }

    recStack.erase(stationId);
    stack.push(stationId);
}

void topologicalSort(std::unordered_map<int, std::vector<Connection>>& graph,
    std::unordered_map<int, PumpingStation>& stations) {
    std::stack<int> stack;
    std::unordered_set<int> visited;
    std::unordered_set<int> recStack;
    bool hasCycle = false;


    for (const auto& station : stations) {
        if (visited.find(station.first) == visited.end()) {
            topologicalSortUtil(station.first, graph, visited, recStack, stack, hasCycle);
            if (hasCycle) {
                std::cout << "ERROR IN GRAPH CYcle" << std::endl;
                return;
            }
        }
    }


    std::cout << "Topological order of the graph:\n";
    while (!stack.empty()) {
        int stationId = stack.top();
        std::cout << "Station ID: " << stationId << ", Name: " << stations[stationId].get_name() << "\n";
        stack.pop();
    }
}

void printGraph(const std::unordered_map<int, std::vector<Connection>>& graph,
    const std::unordered_map<int, PumpingStation>& stations) {
    std::cout << "Graph connections:\n";
    for (const auto& station : stations) {
        std::cout << "Station ID: " << station.first << ", Name: " << station.second.get_name() << " -> ";
        if (graph.find(station.first) != graph.end()) {
            for (const auto& connection : graph.at(station.first)) {
                std::cout << "Connection ID: " << connection.id << " to Station ID: " << connection.targetId << " by Pipe ID: " << connection.pipeId << "; ";
            }
        }
        else {
            std::cout << "No connections.";
        }
        std::cout << "\n";
    }
}