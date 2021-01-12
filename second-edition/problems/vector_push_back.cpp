#include <iostream>
#include <vector>
using namespace std;

int main()
{
  const size_t d = 8;       // 学号共8位.
  int x = 7;                // 随意指定.
  vector<int> V;
  for (size_t i = 0; i < d; i++)
  {
    int num;
    cin >> num;             // 依次输入你的学号, 每次输入1个数字.
    V.push_back(num);
  }
  for (size_t i = 0; i < d; i++)
  {
    V.push_back(V[i] + x);
    V.push_back(V[i] - x);
  }
  for (size_t i = 0; i < V.size(); i++)
    cout << V[i] << endl;
  cout << "The length of V is " << V.size() << endl;
  return 0;
}
