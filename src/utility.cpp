#include "utility.h"

// -------------------- RANDOM --------------------

template<class T> std::random_device  Random<T>::dev;
template<class T> std::mt19937        Random<T>::engine = Random::dev();

template<class T>
Random<T>::Random(T start, T end)
{
    SetInterval(start, end);
}

template<class T>
void Random<T>::SetInterval(T _start, T _end)
{
    start = _start;
    end   = _end;
    distribution = std::uniform_int_distribution<T>(start, end);
}

template<class T>
T Random<T>::operator() ()
{
    return distribution(engine);
}

// -------------------- TIME CHECKER --------------------

TimeChecker::TimeChecker():
    active(false),
    duration(0)
{}

TimeChecker::TimeChecker(int ms):
    TimeChecker()
{
    SetDuration(ms);
}

void TimeChecker::Start()
{
    active = true;
    start = std::chrono::steady_clock::now();
}

void TimeChecker::SetDuration(int ms)
{
    duration{ms};
}

bool TimeChecker::DurationPassed()
{
    if (active)
    {
        std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
        std::chrono::milliseconds delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - start);
        if (delta >= duration)
        {
            active = false;
            return true;
        }
    }
}