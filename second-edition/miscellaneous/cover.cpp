#include <algorithm>
#include <iostream>
#include <string>

int main()
{
  std::string S {"Algorithm Design"};
  std::make_heap(S.begin(), S.end());
  std::sort_heap(S.begin(), S.end());
  auto D = std::unique(S.begin(), S.end());
  std::cout << S.erase(D, S.end()) - S.begin();
  return 0;
}
