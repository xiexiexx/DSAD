module;

#include <ctime>

export module global;

import <iostream>;

// 目前情况下使用import <ctime>;无法运行.

export void old_fashioned()
{
  std::cout << time(NULL) << std::endl;
}