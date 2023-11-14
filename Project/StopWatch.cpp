#include "StopWatch.h"

void gartic::Stopwatch::start()
{
	startTime = std::chrono::high_resolution_clock::now();
}

void gartic::Stopwatch::stop()
{
	endTime = std::chrono::high_resolution_clock::now();
}

float gartic::Stopwatch::elapsed_time()
{
	std::chrono::duration<float> duration = endTime - startTime; //tipul din <> era double
	return duration.count();
}
