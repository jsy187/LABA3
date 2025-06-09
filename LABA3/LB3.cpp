#include <iostream>
#include <fstream>
#include <unordered_map>
#include <chrono>
#include <format>

#include "pipe.h"
#include "pumping_station.h"
#include "utils.h"
#include "pipe_act.h"
#include "pumping_station_act.h"
#include "pipe_sort.h"
#include "pumping_station_sort.h"
#include "pipes_act.h"
#include "file_io.h"
#include "graph.h"

using namespace std;

void handleModifyMultiplePipes(unordered_map<int, Pipe>& pipes) {
    modifyMultiplePipesRepairStatus(pipes);
}

void pipeMenu(unordered_map<int, Pipe>& pipes) {
    int choice;
    do {
        cout << "\nPipe Menu:\n"
            << "1. Add Pipe\n"
            << "2. View All Pipes\n"
            << "3. Modify Pipe Repair Status\n"
            << "4. Delete Pipe\n"
            << "5. Sort/Filter Pipes\n"
            << "6. Modify Multiple Pipes Repair Status\n"
            << "0. Return to Main Menu\n"
            << "Choose an action: ";

        choice = GetCorrectNumber<int>(0, 6);

        switch (choice) {
        case 1: addPipe(pipes); break;
        case 2: viewPipes(pipes); break;
        case 3: modifyPipeRepairStatus(pipes); break;
        case 4: deletePipe(pipes); break;
        case 5: {
            int filterChoice;
            cout << "\nSort/Filter Pipes Menu:\n"
                << "1. Sort by Name\n"
                << "2. Sort by Repair Status\n"
                << "3. Filter by Name\n"
                << "4. Filter by Repair Status\n"
                << "0. Return to Pipe Menu\n"
                << "Choose an action: ";
            filterChoice = GetCorrectNumber<int>(0, 4);

            switch (filterChoice) {
            case 1: sortPipesByName(pipes); break;
            case 2: sortPipesByRepairStatus(pipes); break;
            case 3: filterPipesByName(pipes); break;
            case 4: filterPipesByRepairStatus(pipes); break;
            }
            break;
        }
        case 6: handleModifyMultiplePipes(pipes); break;
        }
    } while (choice != 0);
}

void pumpingStationMenu(unordered_map<int, PumpingStation>& stations) {
    int choice;
    do {
        cout << "\nPumping Station Menu:\n"
            << "1. Add Pumping Station\n"
            << "2. View All Pumping Stations\n"
            << "3. Modify Pumping Station Shops\n"
            << "4. Delete Pumping Station\n"
            << "5. Sort/Filter Pumping Stations\n"
            << "0. Return to Main Menu\n"
            << "Choose an action: ";

        choice = GetCorrectNumber<int>(0, 5);

        switch (choice) {
        case 1: addPumpingStation(stations); break;
        case 2: viewPumpingStations(stations); break;
        case 3: modifyPumpingStationStatus(stations); break;
        case 4: deletePumpingStation(stations); break;
        case 5: {
            int filterChoice;
            cout << "\nSort/Filter Pumping Stations Menu:\n"
                << "1. Sort by Name\n"
                << "2. Sort by Inactive Shops Percentage\n"
                << "3. Filter by Name\n"
                << "4. Filter by Inactive Shops Percentage\n"
                << "0. Return to Pumping Station Menu\n"
                << "Choose an action: ";
            filterChoice = GetCorrectNumber<int>(0, 4);

            switch (filterChoice) {
            case 1: sortPumpingStationsByName(stations); break;
            case 2: sortPumpingStationsByInactiveShopsPercentage(stations); break;
            case 3: filterPumpingStationsByName(stations); break;
            case 4: filterPumpingStationsByInactiveShopsPercentage(stations); break;
            }
            break;
        }
        }
    } while (choice != 0);
}

int main() {
    unordered_map<int, PumpingStation> stations;
    unordered_map<int, Pipe> pipes;
    unordered_map<int, vector<Connection>> graph;

    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y_%H_%M_%OS}", chrono::system_clock::now());
    ofstream logfile("log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    int choice;

    do {
        cout << "\nMain Menu:\n"
            << "1. Pipe Operations\n"
            << "2. Pumping Station Operations\n"
            << "3. Save to File\n"
            << "4. Load from File\n"
            << "5. Connect Stations\n"
            << "6. Print Graph\n"
            << "7. Topological Sort\n"
            << "8. Delete Edge from graph\n"
            << "0. Exit\n"
            << "Choose an action: ";

        choice = GetCorrectNumber<int>(0, 8);

        switch (choice) {
        case 1: pipeMenu(pipes); break;
        case 2: pumpingStationMenu(stations); break;
        case 3: {
            string filename;
            cout << "Enter filename to save data: ";
            cin >> filename;
            saveDataToFile(pipes, stations, filename);
            saveGraphToFile(graph, filename);
            break;
        }
        case 4: {
            string filename;
            cout << "Enter filename to load data: ";
            cin >> filename;
            loadDataFromFile(pipes, stations, filename);
            loadGraphFromFile(graph, filename);
            break;
        }
        case 5: connectStations(pipes, stations, graph); break;
        case 6: printGraph(graph, stations); break;
        case 7: topologicalSort(graph, stations); break;
        case 8: {
            int stid = GetCorrectNumber<int>(1, 20);
            removeEdge(graph, stations, stid);
            break;
        }
        }
    } while (choice != 0);

    cout << "Exiting program.\n";
    return 0;
}