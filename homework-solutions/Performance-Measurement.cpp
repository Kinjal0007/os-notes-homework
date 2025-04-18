#include <iostream>
#include <vector>
#include <queue>
#include <numeric>

struct Process
{
    int id;
    int arrival_time;
    int burst_time;
    int waiting_time = 0;
    int finish_time = 0;
};

void simulate_fcfs(std::vector<Process> &processes)
{
    int current_time = 0;
    std::queue<int> ready_queue;
    std::vector<int> remaining_burst_time(processes.size());

    for (size_t i = 0; i < processes.size(); ++i)
    {
        remaining_burst_time[i] = processes[i].burst_time;
    }

    int completed_processes = 0;
    while (completed_processes < processes.size())
    {
        for (size_t i = 0; i < processes.size(); ++i)
        {
            if (processes[i].arrival_time <= current_time && remaining_burst_time[i] > 0)
            {
                if (std::find(ready_queue.front(), ready_queue.back(), processes[i].id) == ready_queue.back())
                {
                    ready_queue.push(processes[i].id);
                }
            }
        }

        if (!ready_queue.empty())
        {
            int current_process_id = ready_queue.front();
            ready_queue.pop();
            auto process_it = std::find_if(processes.begin(), processes.end(), [&](const Process &p)
                                           { return p.id == current_process_id; });

            if (process_it != processes.end())
            {
                if (process_it->finish_time == 0)
                {
                    process_it->waiting_time = current_time - process_it->arrival_time;
                }

                current_time += remaining_burst_time[process_it - processes.begin()];
                remaining_burst_time[process_it - processes.begin()] = 0;
                process_it->finish_time = current_time;
                completed_processes++;
            }
        }
        else
        {
            current_time++;
        }
    }
}

int main()
{
    std::vector<Process> processes = {
        {1, 0, 5},
        {2, 1, 3},
        {3, 2, 8}};

    simulate_fcfs(processes);

    std::cout << "FCFS Scheduling Simulation Results:\n";
    std::cout << "Process ID | Arrival Time | Burst Time | Waiting Time | Finish Time\n";
    std::cout << "-----------|--------------|------------|--------------|-------------\n";
    for (const auto &p : processes)
    {
        std::cout << p.id << "          | " << p.arrival_time << "            | " << p.burst_time << "          | " << p.waiting_time << "            | " << p.finish_time << "\n";
    }

    double total_waiting_time = std::accumulate(processes.begin(), processes.end(), 0.0,
                                                [](double sum, const Process &p)
                                                {
                                                    return sum + p.waiting_time;
                                                });
    double average_waiting_time = total_waiting_time / processes.size();
    std::cout << "\nAverage Waiting Time: " << average_waiting_time << "\n";

    return 0;
}