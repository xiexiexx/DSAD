export module LEGO;

import matrix;
import <iostream>;
import <iomanip>;

struct point {
  size_t x, y;  // 点的x坐标和y坐标.
};

export class LEGO {
public:
  // 构造函数.
  LEGO(size_t n)
    : baseplate(n, n), length(n)
  {
    // 设定尺寸, 注意初始点到求解时再行设定.
  }

  // 设定已铺平瓦的位置singularity并求解.
  void solve(point singularity)
  {
    // 初始已铺平瓦位置编号为0.
    baseplate(singularity.x, singularity.y) = 0;
    label = 1;
    DAC(length, {0, 0}, singularity);
  }

  // 打印解法.
  void print(int width)
  {
    for (size_t i = 0; i < length; ++i)
    {
      for (size_t j = 0; j < length; ++j)
        std::cout << std::setw(width) << baseplate(i, j);
      std::cout << std::endl;
    }
  }

private:
  // n为所求解底板当前边长, start为该底板左上角位置,
  // singularity为当前底板中已铺位置. 采用分治法DAC求解.
  void DAC(size_t n, point start, point singularity)
  {
    if (n > 1)
    {
      size_t half = n / 2;
      // positions描述更小底板的已铺位置坐标.
      point positions[2][2];
      // 先统一给出中心位置4个点的坐标, 也可用for语句实现(但稍慢).
      positions[0][0] = {start.x + half - 1, start.y + half - 1};
      positions[0][1] = {start.x + half - 1, start.y + half};
      positions[1][0] = {start.x + half, start.y + half - 1};
      positions[1][1] = {start.x + half, start.y + half};
      // 再将中心位置4个点中不需要铺砖的位置改为真正的已铺位置.
      size_t p = (singularity.x - start.x) / half;
      size_t q = (singularity.y - start.y) / half;
      positions[p][q] = singularity;
      // 暂时保存不需要铺砖的位置原有的值.
      size_t temp = baseplate(positions[p][q].x, positions[p][q].y);
      // 对中心位置进行一次铺砖操作
      baseplate(positions[0][0].x, positions[0][0].y) = label;
      baseplate(positions[0][1].x, positions[0][1].y) = label;
      baseplate(positions[1][0].x, positions[1][0].y) = label;
      baseplate(positions[1][1].x, positions[1][1].y) = label;
      // 恢复不需要铺砖的位置原有的值, 此方式避免了判断语句.
      baseplate(positions[p][q].x, positions[p][q].y) = temp;
      // 所铺砖的编号增1, 为下次铺砖准备.
      ++label;
      // 最后平均分割为4块较小尺寸的底板进行递归铺砖.
      DAC(half, {start.x, start.y}, positions[0][0]);
      DAC(half, {start.x, start.y + half}, positions[0][1]);
      DAC(half, {start.x + half, start.y}, positions[1][0]);
      DAC(half, {start.x + half, start.y + half}, positions[1][1]);
    }
  }

  matrix<size_t> baseplate; // 存储底板编号数据的矩阵.
  size_t length;            // 底板长度.
  size_t label;             // 编号, 为新铺砖标记编号且不断增加.
};
