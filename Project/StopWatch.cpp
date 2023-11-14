#include "StopWatch.h"

void gartic::Stopwatch::start()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void gartic::Stopwatch::stop()
{
	endTime = std::chrono::high_resolution_clock::now();
}

double gartic::Stopwatch::elapsed_time()
{
	std::chrono::duration<double> duration = endTime - startTime;
	return duration.count();
}
