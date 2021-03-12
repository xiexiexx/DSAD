#include <iostream>
using namespace std;

int main()
{
  int x;
  cin >> x;               // 输入
  const int N = 10000;    // 数组长度
  char data[N];           // 字符数组
  const int M = 26;       // 模
  for (int i = 0; i < N; ++i)
  {
    x = (x * x) % M;
    data[i] = x + 'a';
  }
  cout << data[N - 1];    // 输出
  return 0;
}
