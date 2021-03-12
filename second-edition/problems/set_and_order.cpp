#include <iostream>
#include <set>
using namespace std;

int main()
{
  const int d = 8;        // 学号共8位.
  const int W = 10;       // 权值.
  int x = 7;              // 随意指定.
  set<int> S;
  for (int i = 0; i < d; ++i)
  {
    int num;
    cin >> num;           // 依次输入你的学号, 每次输入1个数字
    S.insert(W * i + num + d + x);
    S.insert(- W * i - num - d - x);
  }
  for (auto iter = S.begin(); iter != S.end(); ++iter)
    cout << *iter << " ";
  cout << endl;
  while (S.size() > 0)
  {
    cout << *S.rbegin() << " ";
    S.erase(--S.end());
  }
  cout << endl;
  return 0;
}
