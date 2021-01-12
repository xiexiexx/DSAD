#include <iostream>
#include <vector>
#include <list>
using namespace std;

int main()
{
  const int d = 8;
  const int w = 3;
  const int MAX = 10;
  vector<int> V(d);
  list<int> L;
  for(int i = 0; i < d; i++)
  {
    cin >> V[i];
    L.push_back(V[i]);
  }
  auto iter = L.begin();
  int x = 0;
  for(int i = 0; i < MAX; i++)
  {
    for(int j = 0; j < w; j++)
    {
      #ifndef _MSC_VER  // 非Visual C++环境.
        ++iter;
      #else
        if (iter == L.end())
          iter = L.begin();
        else
          ++iter;
      #endif
      x = (x + w) % d;
    }
    if(V[x] % 2 == 1)
    {
      L.insert(iter, V[x]);
      V[x] *= 2;
    }
    else
    {
      V[x]++;
      if(iter != L.end())
        iter = L.erase(iter);
    }
  }
  for(auto citer = L.cbegin(); citer != L.cend(); ++citer)
    cout << *citer << " ";
  return 0;
}
