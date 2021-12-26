#include <chrono>
#include <random>

template <typename T>
class Random
{
  static std::random_device dev;
  static std::mt19937 engine;

  std::uniform_int_distribution<T> distribution;
  T start, end;

public:
  Random(T start, T end);
  void SetInterval(T _start, T _end);
  void operator();
};

class TimeChecker
{
  std::chrono::time_point<std::chrono::steady_clock> start;
  std::chrono::milliseconds duration;
  bool active;
public:
  TimeChecker();
  TimeChecker(int duration);

  void Start();
  void SetDuration(int milliseconds);
  bool DurationPassed();
  bool GetActive() { return active; }
};