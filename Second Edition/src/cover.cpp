#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
  string S = "Algorithm Design";
  make_heap(S.begin(), S.end());
  sort_heap(S.begin(), S.end());
  auto D = unique(S.begin(), S.end());
  cout << S.erase(D, S.end()) - S.begin();
  return 0;
}
