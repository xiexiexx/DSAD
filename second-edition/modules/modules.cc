import <iostream>;
import <list>;

import identity_matrix;
import timer;
import slow_Fibonacci;
import LEGO;
import ChiaHsien_triangle;
import special_statistic;
import multi_treasure_hunting;
import print_all;
import prefixsum;
import shuffling;
import global;

// 以下演示程序可直接在main函数中调用.

// 单位矩阵演示.
void demo_identity_matrix()
{
  // 设置5阶单位矩阵并打印.
  identity_matrix(5);
}

// Fibonacci序列计算(非常慢).
void demo_Fibonacci()
{
  // 设置计时器t.
  timer t;
  // 计时开始.
  t.start();
  Fibonacci_sequence(50);
  // 计时结束.
  t.stop();
  // 打印时长.
  std::cout << t.time() << std::endl;
}

// LEGO问题求解.
void demo_LEGO()
{
  // 底板边长为8, 初始已覆盖(5, 2)位置.
  LEGO L(8);
  L.solve({5, 2});
  // 80字符终端打印可设width为5.
  L.print(5);
}

// 贾宪三角演示.
void demo_ChiaHsien_triangle()
{
  // 由于终端显示限制n最大取13.
  // 二项式系数的宽度width, 随n的值增大而增大, 此处取3足矣.
  ChiaHsien_triangle(13, 3);
}

// 统计量问题演示.
void demo_special_statistic()
{
  std::list<int> L;
  int d = 2;
  special_statistic(L, d);
}

// 寻找宝藏问题演示.
void demo_multi_treasure_hunting()
{
  std::vector<std::vector<std::string>> H {
    {"A", "B"}, {"B", "A"}, {"D", "S", "A", "D"}
  };
  std::vector<std::string> F {"B", "B", "S"};
  multi_treasure_hunting(H, F);
}

// 前缀和问题演示.
void demo_prefixsum()
{
  std::vector<double> A {3.1, 3.14, 3.141, 3.1415};
  std::vector<double> S(A.size());
  // 将A的部分和逐个存于S之中.
  prefixsum(A, S);
  print_all(S);
}

// 洗牌算法展示.
void demo_shuffling()
{
  std::vector<int> V {4, 2, 1, 3, 5};
  // 洗牌n次.
  size_t n = 3;
  for (size_t i = 0; i < n; ++i)
  {
    shuffling(V);
    print_all(V.begin(), V.end());
  }
}

// 在模块中使用头文件.
void demo_global()
{
  old_fashioned();
}

int main()
{
  // 添加演示函数即可.
  return 0;
}
