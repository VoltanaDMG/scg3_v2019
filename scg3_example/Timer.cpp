#include <chrono> // Needed for struct timer
#include <iostream> // Already included, see above
#include "Timer.h"

Timer::Timer() { }


Timer::~Timer() { }

TimerSP Timer::create()
{
	return std::make_shared<Timer>();
}

Timer* Timer::reset() 
{
	start = clock::now();
	return this;
}

unsigned long long Timer::milliseconds_elapsed() const
{
	return std::chrono::duration_cast<milliseconds>(clock::now() - start).count();
}
