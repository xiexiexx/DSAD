#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

void ChiaHsien_triangle(uint64_t n, int width)
{
  // 以宽度width打印关于整数n的贾宪三角,
  std::queue<uint64_t> Q;
  Q.push(1);	// 第0行仅有1个元素.
  for(uint64_t i = 0; i < n + 1; i++)
  {
    // 以(n - i) * width为宽度打印前导空格.
    std::cout << std::string((n - i) * width, ' ');;
    uint64_t prev = 0;
    // 打印当前行并生成下一行新元素.
    for(uint64_t j = 0; j < i + 1; j++)
    {
      // 每项及其后的空格均占width宽度.
      std::cout << std::setw(width) << Q.front()
                << std::string(width, ' ');
      // 当前元素Q.front()与前一个出队元素prev相加形成下一行新元素.
      Q.push( prev + Q.front() );
      prev = Q.front();	// 更新prev以便下次使用.
      Q.pop();
    }
    Q.push(1);	// 最后得补上下一行行尾的1.
    std::cout << std::endl;
  }
}
