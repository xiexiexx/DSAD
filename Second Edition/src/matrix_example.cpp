#include <iostream>
#include <matrix.h>
using namespace std;

int main()
{
  const size_t n = 5;
  matrix<int> M(n, n, 0);
  // 对角线赋值.
  for (size_t i = 0; i < M.xsize(); i++)
    M(i, i) = 1;
  // 在屏幕上输出该矩阵.
  for (size_t i = 0; i < M.xsize(); i++)
  {
    for (size_t j = 0; j < M.ysize(); j++)
      cout << M(i, j) << " ";
    cout << endl;
  }
  return 0;
}