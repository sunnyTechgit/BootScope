CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude

TARGET = bin/bootscope
SRC = src/main.cpp src/SystemInfo.cpp src/BootProfiler.cpp src/ServiceAnalyzer.cpp src/BootAnalyzer.cpp src/PerformanceAnalyzer.cpp
all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET)

run: all
	./$(TARGET)
