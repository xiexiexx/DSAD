#include <iostream>
#include "matrix.h"

void identity_matrix(size_t n)
{
  matrix<int> M(n, n, 0);
  // 对角线赋值.
  for (size_t i = 0; i < M.x_size(); i++)
    M(i, i) = 1;
  // 按行列打印该矩阵.
  for (size_t i = 0; i < M.x_size(); i++)
  {
    for (size_t j = 0; j < M.y_size(); j++)
      std::cout << M(i, j) << " ";
    std::cout << std::endl;
  }
}
