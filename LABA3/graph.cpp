#include "graph.h"
#include <iostream>
#include "pipe_act.h"
#include "utils.h"

using namespace std;

void connectStations(unordered_map<int, Pipe>& pipes,
    unordered_map<int, PumpingStation>& stations,
    unordered_map<int, vector<Connection>>& graph) {
    int sourceId = GetCorrectNumber<int>(0,100);
    int targetId = GetCorrectNumber<int>(0,100);
    int diameter = GetCorrectNumber<int>(500, 1400);

    if (diameter != 500 && diameter != 700 && diameter != 1000 && diameter != 1400) {
        cerr << "Error: Invalid diameter. Allowed values: 500, 700, 1000, 1400.\n";
        return;
    }

    if (stations.find(sourceId) == stations.end() || stations.find(targetId) == stations.end()) {
        cerr << "Error: One or both stations do not exist.\n";
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
        cout << "No available pipe with diameter " << diameter << ". Create a new pipe.\n";
        addPipe(pipes);
        pipeId = Pipe::get_MaxID();
    }

    Connection connection{ static_cast<int>(graph.size() + 1), pipeId, sourceId, targetId };
    graph[sourceId].push_back(connection);

    cout << "Stations connected successfully.\n";
}

void removeEdge(unordered_map<int, vector<Connection>>& graph,
    unordered_map<int, PumpingStation>& stations, int stid) {
    if (stations.find(stid) == stations.end()) {
        cerr << "Error: Pumping station with ID " << stid << " not found.\n";
        return;
    }
    stations.erase(stid);
    for (auto& [sourceId, connections] : graph) {
        connections.erase(remove_if(connections.begin(), connections.end(), [stid](const Connection& con) {
            return con.sourceId == stid || con.targetId == stid;
            }), connections.end());
    }
    graph.erase(stid);
    cout << "Deleted station with ID: " << stid << "\n";
}

void topologicalSortUtil(int stationId,
    unordered_map<int, vector<Connection>>& graph,
    unordered_set<int>& visited,
    unordered_set<int>& recStack,
    stack<int>& result,
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
            topologicalSortUtil(connection.targetId, graph, visited, recStack, result, hasCycle);
        }
    }

    recStack.erase(stationId);
    result.push(stationId);
}

void topologicalSort(unordered_map<int, vector<Connection>>& graph,
    unordered_map<int, PumpingStation>& stations) {
    stack<int> result;
    unordered_set<int> visited;
    unordered_set<int> recStack;
    bool hasCycle = false;

    for (const auto& station : stations) {
        if (visited.find(station.first) == visited.end()) {
            topologicalSortUtil(station.first, graph, visited, recStack, result, hasCycle);
            if (hasCycle) {
                cerr << "ERROR: Graph contains a cycle.\n";
                return;
            }
        }
    }


    cout << "Topological order of the graph:\n";
    while (!result.empty()) {
        int stationId = result.top();
        cout << "Station ID: " << stationId << ", Name: " << stations[stationId].get_name() << "\n";
        result.pop();
    }
}

void printGraph(const unordered_map<int, vector<Connection>>& graph,
    const unordered_map<int, PumpingStation>& stations) {
    cout << "Graph connections:\n";
    for (const auto& station : stations) {
        cout << "Station ID: " << station.first << ", Name: " << station.second.get_name() << " -> ";
        if (graph.find(station.first) != graph.end()) {
            for (const auto& connection : graph.at(station.first)) {
                cout << "Connection ID: " << connection.id
                    << ", to Station ID: " << connection.targetId
                    << ", by Pipe ID: " << connection.pipeId << "; ";
            }
        }
        else {
            cout << "No connections.";
        }
        cout << "\n";
    }
}