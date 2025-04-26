#include <iostream>
#include <sys/time.h>
#include <unistd.h>
#include <vector>
#include <cmath>
#include <time.h>

class Timer
{
public:
    static uint64_t get_ns()
    {
        struct timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        return (uint64_t)ts.tv_sec * 1000000000ULL + ts.tv_nsec;
    }

    static double measure_clock_overhead()
    {
        const int iterations = 1000000;
        uint64_t start = get_ns();

        for (int i = 0; i < iterations; i++)
        {
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
        }

        uint64_t end = get_ns();
        return (end - start) / (double)iterations / 1000.0; // Convert to microseconds
    }
};

class SystemCallMeasurement
{
private:
    std::vector<double> measurements;
    int num_iterations;

public:
    SystemCallMeasurement(int iterations = 100000)
        : num_iterations(iterations) {}

    void measure()
    {
        measurements.clear();

        for (int i = 0; i < num_iterations; i++)
        {
            uint64_t start = Timer::get_ns();
            read(STDIN_FILENO, NULL, 0); // Null read system call
            uint64_t end = Timer::get_ns();
            measurements.push_back((end - start) / 1000.0); // Convert to microseconds
        }
    }

    double get_mean() const
    {
        double sum = 0;
        for (double m : measurements)
        {
            sum += m;
        }
        return sum / measurements.size();
    }

    double get_std_dev() const
    {
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
        std::cout << "System Call Measurement Results:\n";
        std::cout << "Number of iterations: " << num_iterations << "\n";
        std::cout << "Mean time per system call: " << get_mean() << " microseconds\n";
        std::cout << "Standard deviation: " << get_std_dev() << " microseconds\n";
    }
};

int main()
{
    // Measure timer overhead
    std::cout << "Timer Overhead Measurements:\n";
    std::cout << "clock_gettime overhead: " << Timer::measure_clock_overhead() << " microseconds\n\n";

    // Measure system calls
    SystemCallMeasurement measurement(100000);
    measurement.measure();
    measurement.print_results();

    return 0;
}