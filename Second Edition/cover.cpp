#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

int main()
{
  string D = "algorithm design";
  make_heap(D.begin(), D.end());
  sort_heap(D.begin(), D.end());
  D.erase(unique(D.begin(), D.end()), D.end());
  return 0;
}
