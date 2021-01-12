#include "matrix.h"

#ifndef LEGO_CLASS
#define LEGO_CLASS

struct point {
  size_t x, y;
};

class LEGO {
public:
  // 构造函数.
  LEGO(size_t n, point init_spot);
  // 求解.
  void solve();
  // 打印解法.
  void print();
private:
  // n为所求解底板当前边长, start为该底板左上角位置,
  // spot为当前底板中已铺位置. 采用分治法DAC求解.
  void DAC(size_t n, point start, point spot);
  matrix<size_t> baseplate;	// 存储底板编号数据的矩阵.
  point init_spot;          // 初始已铺平瓦的位置坐标.
  size_t length;						// 底板长度.
  size_t label;             // 编号, 为新铺砖标记编号且不断增加.
};

#endif
