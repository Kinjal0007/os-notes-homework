#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <sys/wait.h>
#include <sched.h>
#include <string.h>
#include <time.h>

// This is a macOS build, so we'll skip the CPU binding since it requires special privileges
bool bind_to_cpu(int cpu_id)
{
    std::cout << "Note: CPU binding not implemented for macOS in this version\n";
    return true; // Just return success, we'll measure without binding
}

class ContextSwitchMeasurement
{
private:
    int num_iterations;
    int pipe1[2]; // Parent writes to child
    int pipe2[2]; // Child writes to parent
    std::vector<double> measurements;

public:
    static uint64_t get_ns()
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
    }

    ContextSwitchMeasurement(int iterations = 10000)
        : num_iterations(iterations)
    {
        if (pipe(pipe1) < 0 || pipe(pipe2) < 0)
        {
            perror("pipe");
            exit(1);
        }
    }

    ~ContextSwitchMeasurement()
    {
        close(pipe1[0]);
        close(pipe1[1]);
        close(pipe2[0]);
        close(pipe2[1]);
    }

    void measure()
    {
        // Try to bind current process to CPU 0
        bind_to_cpu(0);

        pid_t child_pid = fork();
        if (child_pid < 0)
        {
            perror("fork");
            return;
        }

        if (child_pid == 0)
        { // Child process
            // Try to bind child to same CPU
            bind_to_cpu(0);

            char buf[1];
            for (int i = 0; i < num_iterations; i++)
            {
                // Read from parent
                if (read(pipe1[0], buf, 1) != 1)
                {
                    perror("child read");
                    exit(1);
                }
                // Write to parent
                if (write(pipe2[1], "c", 1) != 1)
                {
                    perror("child write");
                    exit(1);
                }
            }
            exit(0);
        }
        else
        { // Parent process
            measurements.clear();
            char buf[1];

            for (int i = 0; i < num_iterations; i++)
            {
                uint64_t start = get_ns();

                // Write to child
                if (write(pipe1[1], "p", 1) != 1)
                {
                    perror("parent write");
                    return;
                }
                // Read from child
                if (read(pipe2[0], buf, 1) != 1)
                {
                    perror("parent read");
                    return;
                }

                uint64_t end = get_ns();
                measurements.push_back((end - start) / 1000.0); // Convert to microseconds
            }

            // Wait for child to finish
            wait(NULL);
        }
    }

    double get_mean() const
    {
        if (measurements.empty())
            return 0.0;
        double sum = 0;
        for (double m : measurements)
        {
            sum += m;
        }
        return sum / measurements.size();
    }

    double get_std_dev() const
    {
        if (measurements.empty())
            return 0.0;
        double mean = get_mean();
        double sum_sq_diff = 0;

        for (double m : measurements)
        {
            double diff = m - mean;
            sum_sq_diff += diff * diff;
        }

        return sqrt(sum_sq_diff / measurements.size());
    }

    void print_results() const
    {
        std::cout << "Context Switch Measurement Results:\n";
        std::cout << "Number of iterations: " << num_iterations << "\n";
        std::cout << "Mean time per context switch: " << get_mean() / 2 << " microseconds\n";
        std::cout << "Standard deviation: " << get_std_dev() / 2 << " microseconds\n";
    }
};

int main()
{
    std::cout << "Measuring context switch costs...\n\n";

    ContextSwitchMeasurement measurement(10000);
    measurement.measure();
    measurement.print_results();

    return 0;
}