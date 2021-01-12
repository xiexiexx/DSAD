#ifndef TIMER_CLASS
#define TIMER_CLASS

#include <ctime>

class xTimer {
private:
	std::clock_t startTime;
	std::clock_t endTime;
public:
	xTimer();
	void start();
	void stop();
	double time() const;
};

// 以下xTimer类实现都使用了inline形式.

inline xTimer::xTimer()
	: startTime(0), endTime(0)
{}

// 计时开始.
inline void xTimer::start()
{
	startTime = std::clock();
}

// 计时结束.
inline void xTimer::stop()
{
	endTime = std::clock();
}

// 返回计时时间.
inline double xTimer::time() const
{
	return static_cast<double>(endTime - startTime)
		/ static_cast<double>(CLOCKS_PER_SEC);
	// 注意转换的是double型，否则可能对应类似整数的除法结果, 产生错误.
	// 一般CLOCKS_PER_SEC为整数1000.
}

#endif // TIMER_CLASS
