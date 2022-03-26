export module timer;

import <chrono>;

export class timer {
public:
  // 计时开始.
  void start()
  {
    s = std::chrono::steady_clock::now();
  }

  // 计时结束.
  void stop()
  {
    e = std::chrono::steady_clock::now();
  }

  // 返回计时时间(以秒计).
  double time() const
  {
    return std::chrono::duration<double>(e - s).count();
  }

private:
  // s和e分别是开始和结束时间.
  std::chrono::time_point<std::chrono::steady_clock> s, e;
};
