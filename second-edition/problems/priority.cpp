#include <iostream>
#include <queue>
using namespace std;

int main()
{
  const int d = 8;          // 学号共8位
  int x = 7;                // 在课堂上当场指定
  priority_queue<int> PQ;
  for (int i = 0; i < d; ++i)
  {
    int num;
    cin >> num;             // 依次输入你的学号, 每次输入1个数字
    PQ.push(x * i + num);
    x = -x;
  }
  while (PQ.size() > 1)
  {
    int r1 = PQ.top();
    PQ.pop();
    int r2 = PQ.top();
    PQ.pop();
    PQ.push(r1 - r2);
    cout << r1 + r2 << " ";
  }
  cout << endl << PQ.size();
  return 0;
}
