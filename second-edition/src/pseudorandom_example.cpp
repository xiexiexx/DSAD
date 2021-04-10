#include <iostream>

const int A = 48271;
const int M = 2147483647;
const int Q = M / A;
const int R = M % A;

// 将X更改为伪随机整数序列的下一个数, 其范围仍保持(0, M).
void pseudorandom(int& X)
{
  X = A * (X % Q) - R * (X / Q);
  if (X < 0)
    X += M;
}

// 打印n个[0, m)内的伪随机数, 初始种子值为seed.
int main()
{
  int seed = 314159;  // 取值限定为(0, M)范围内.
  int n = 42;
  int m = 73;
  for (int i = 0; i < n; ++i)
  {
    pseudorandom(seed);
    double r = static_cast<double>(seed) / static_cast<double>(M);
    std::cout << static_cast<int>(r * m) << ' ';
  }
  return 0;
}
