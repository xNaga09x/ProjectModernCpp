#pragma once
import <iostream>;
import <chrono>;
import <thread>;
namespace gartic {

	class Stopwatch {
	private:
		std::chrono::high_resolution_clock::time_point startTime;
		std::chrono::high_resolution_clock::time_point endTime;

	public:
		Stopwatch() {}
		void start()
		{
			startTime = std::chrono::high_resolution_clock::now();
		}

		void stop()
		{
			endTime = std::chrono::high_resolution_clock::now();
		}

		double elapsed_time()
		{
			std::chrono::duration<double> duration = endTime - startTime;
			return duration.count();
		}
	};
}