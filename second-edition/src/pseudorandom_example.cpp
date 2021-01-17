#include <iostream>

const int A = 48271;
const int M = 2147483647;
const int Q = M / A;
const int R = M % A;

// 将X更改为伪随机整数序列的下一个数, 其范围仍保持(0, M).
void random(int& X)
{
  X = A * (X % Q) - R * (X / Q);
  if (X < 0)
    X += M;
}

// 在屏幕上输出42个[0,100)内的伪随机数, 初始种子值为202111.
int main()
{
  int seed = 202111;  // 取值区间为(0, M).
  int n = 100;
  for (int i = 0; i < 42; i++)
  {
    random(seed);
    double r = static_cast<double>(seed) / static_cast<double>(M);
    std::cout << static_cast<int>(r * n) << ' ';
  }
  return 0;
}
