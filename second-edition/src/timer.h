#ifndef TIMER_CLASS
#define TIMER_CLASS

#include <chrono>

class timer {
public:
  void start();
  void stop();
  double time() const;
private:
  // s和e分别是开始和结束时间.
  std::chrono::time_point<std::chrono::steady_clock> s, e;
};

// 以下timer类实现都使用了inline形式.

// 计时开始.
inline void timer::start()
{
  s = std::chrono::steady_clock::now();
}

// 计时结束.
inline void timer::stop()
{
  e = std::chrono::steady_clock::now();
}

// 返回计时时间(以秒计).
inline double timer::time() const
{
  return std::chrono::duration<double>(e - s).count();
}

#endif  // TIMER_CLASS
