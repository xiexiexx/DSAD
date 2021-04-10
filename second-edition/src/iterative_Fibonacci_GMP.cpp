#include <iostream>
// 需要安装GMP库(https://gmplib.org).
#include "gmp.h"

int main()
{
  // F[i]表示Fibonacci序列中下标为i的项.
  // m2, m1, f分别代表F[n - 2], F[n - 1], F[n].
  mpz_t m2, m1, f;
  // 以字符串形式赋值m2和m1, 分别取10进制的0和1.
  mpz_init_set_str(m2, "0", 10);
  mpz_init_set_str(m1, "1", 10);
  // 初始化f(无任何值).
  mpz_init(f);
  size_t n = 2021;
  for (size_t i = 2; i < n; ++i)
  {
    // mpz_add可理解为将m2 + m1的结果赋予f.
    mpz_add(f, m2, m1);
    // mpz_set(x, y)是将y的值赋予x.
    mpz_set(m2, m1);
    mpz_set(m1, f);
  }
  mpz_add(f, m2, m1);
  std::cout << "Fibonacci " << n << std::endl;
  // 打印f的值.
  gmp_printf("%Zd\n", f);
  // 释放所有整数变量的空间, 注意列表要以NULL结尾.
  mpz_clears(m2, m1, f, NULL);
  return 0;
}
