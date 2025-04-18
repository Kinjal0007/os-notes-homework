#include <iostream>
#include <vector>
#include <queue>
#include <numeric> // For std::accumulate

using namespace std;

// Structure to represent a process
struct Process {
    int id;
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int finishTime;
};

// Function to simulate First-Come, First-Served (FCFS) CPU scheduling
void simulateFCFS(vector<Process>& processes) {
    int currentTime = 0;
    queue<int> readyQueue;
    vector<int> remainingBurstTime(processes.size());
    for (size_t i = 0; i < processes.size(); ++i) {
        remainingBurstTime[i] = processes[i].burstTime;
        processes[i].waitingTime = 0;
        processes[i].finishTime = 0;
    }

    int completedProcesses = 0;
    while (completedProcesses < processes.size()) {
        // Add arriving processes to the ready queue
        for (size_t i = 0; i < processes.size(); ++i) {
            if (processes[i].arrivalTime <= currentTime && remainingBurstTime[i] > 0) {
                bool alreadyInQueue = false;
                queue<int> tempQueue = readyQueue;
                while (!tempQueue.empty()) {
                    if (tempQueue.front() == processes[i].id) {
                        alreadyInQueue = true;
                        break;
                    }
                    tempQueue.pop();
                }
                if (!alreadyInQueue) {
                    readyQueue.push(processes[i].id);
                }
            }
        }

        if (!readyQueue.empty()) {
            int currentProcessId = readyQueue.front();
            readyQueue.pop();
            int processIndex = -1;
            for (size_t i = 0; i < processes.size(); ++i) {
                if (processes[i].id == currentProcessId) {
                    processIndex = i;
                    break;
                }
            }

            if (processIndex != -1) {
                // Calculate waiting time if it's the first time the process runs
                if (processes[processIndex].finishTime == 0) {
                    processes[processIndex].waitingTime = currentTime - processes[processIndex].arrivalTime;
                }

                // Simulate execution
                currentTime += remainingBurstTime[processIndex];
                remainingBurstTime[processIndex] = 0;
                processes[processIndex].finishTime = currentTime;
                completedProcesses++;
            }
        } else {
            currentTime++; // If no process is ready, advance time
        }
    }
}

int main() {
    // Example processes
    vector<Process> processes = {
        {1, 0, 5, 0, 0},
        {2, 1, 3, 0, 0},
        {3, 2, 8, 0, 0}
    };

    simulateFCFS(processes);

    cout << "FCFS Scheduling Simulation Results:\n";
    cout << "Process ID | Arrival Time | Burst Time | Waiting Time | Finish Time\n";
    cout << "-----------|--------------|------------|--------------|-------------\n";
    for (const auto& p : processes) {
        cout << p.id << "          | " << p.arrivalTime << "            | " << p.burstTime << "          | " << p.waitingTime << "            | " << p.finishTime << "\n";
    }

    // Calculate and display average waiting time
    double totalWaitingTime = accumulate(processes.begin(), processes.end(), 0.0,
                                             [](double sum, const Process& p) {
                                                 return sum + p.waitingTime;
                                             });
    double averageWaitingTime = totalWaitingTime / processes.size();
    cout << "\nAverage Waiting Time: " << averageWaitingTime << "\n";

    return 0;
}
