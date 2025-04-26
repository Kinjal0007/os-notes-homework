CXX = g++
CXXFLAGS = -O2 -Wall -std=c++11 -D_GNU_SOURCE

all: measure_syscall measure_context_switch

measure_syscall: measure_syscall.cpp
	$(CXX) $(CXXFLAGS) -o measure_syscall measure_syscall.cpp

measure_context_switch: measure_context_switch.cpp
	$(CXX) $(CXXFLAGS) -o measure_context_switch measure_context_switch.cpp

clean:
	rm -f measure_syscall measure_context_switch 