#include <queue>
#include <iostream>
#include <string>
#include <iomanip>

void ChiaHsienTriangle(int n)
{
  // 打印贾宪三角的前n + 1行, 由于宽度限制n最大取12.
  // 二项式系数的宽度, 随n的值增大而增大, 此处取3足矣.
  int width = 3;
  std::queue<int> Q;
  Q.push(1);	// 第0行仅有1个元素.
  for(int i = 0; i < n + 1; i++)
  {
    for(int j = 0; j < n - i; j++)
      // 以(n - i) * width为宽度打印前导空格.
      std::cout << std::string(width, ' ');
    int prev = 0;
    // 打印当前行并生成下一行新元素.
    for(int j = 0; j < i + 1; j++)
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
