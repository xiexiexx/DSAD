#include <iostream>
// 需要安装GMP库(https://gmplib.org). 
#include "gmp.h"

int main()
{
  // m2, m1, f分别代表f_{n - 2}, f_{n - 1}, f_{n}.
  mpz_t m2, m1, f;
  // 以字符串形式赋值m2和m1, 取10进制的0和1.
  mpz_init_set_str(m2, "0", 10);
  mpz_init_set_str(m1, "1", 10);
  // 初始化f.
  mpz_init(f);
  size_t n = 2021;
  for (size_t i = 2; i <= n; ++i)
  {
    mpz_add(f, m2, m1);
    mpz_set(m2, m1);
    mpz_set(m1, f);
  }
  std::cout << "Fibonacci " << n << std::endl;
  gmp_printf("%Zd\n", f);
  // 释放所有整数变量的空间, 注意列表要以NULL结尾.
  mpz_clears(m2, m1, f, NULL);
  return 0;
}
