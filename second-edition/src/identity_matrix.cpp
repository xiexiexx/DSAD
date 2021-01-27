#include <iostream>
#include "matrix.h"

void identity_matrix(size_t n)
{
  matrix<int> M(n, n, 0);
  // 对角线赋值.
  for (size_t i = 0; i < M.xsize(); i++)
    M(i, i) = 1;
  // 按行列打印该矩阵.
  for (size_t i = 0; i < M.xsize(); i++)
  {
    for (size_t j = 0; j < M.ysize(); j++)
      std::cout << M(i, j) << " ";
    std::cout << std::endl;
  }
}
