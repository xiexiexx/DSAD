#include "LEGO.h"
#include <iostream>
#include <iomanip>

LEGO::LEGO(size_t n)
  : baseplate(n, n), length(n)
{
  // 设定尺寸, 注意初始点到求解时再行设定.
}

void LEGO::DAC(size_t n, point start, point spot)
{
  if (n > 1)
  {
    size_t half = n / 2;
    // spot_temp描述更小底板的已铺位置坐标.
    point spot_temp[2][2];
    // 先统一给出中心位置4个点的坐标, 也可用for语句实现(但稍慢).
    spot_temp[0][0] = {start.x + half - 1, start.y + half - 1};
    spot_temp[0][1] = {start.x + half - 1, start.y + half};
    spot_temp[1][0] = {start.x + half, start.y + half - 1};
    spot_temp[1][1] = {start.x + half, start.y + half};
    // 再将中心位置4个点中不需要铺砖的位置为真正的已铺位置.
    size_t p = (spot.x - start.x) / half;
    size_t q = (spot.y - start.y) / half;
    spot_temp[p][q] = {spot.x, spot.y};
    // 暂时保存不需要铺砖的位置原有的值.
    size_t temp = baseplate(spot_temp[p][q].x, spot_temp[p][q].y);
    // 对中心位置进行一次铺砖操作
    baseplate(spot_temp[0][0].x, spot_temp[0][0].y) = label;
    baseplate(spot_temp[0][1].x, spot_temp[0][1].y) = label;
    baseplate(spot_temp[1][0].x, spot_temp[1][0].y) = label;
    baseplate(spot_temp[1][1].x, spot_temp[1][1].y) = label;
    // 恢复不需要铺砖的位置原有的值, 此方式避免了判断语句.
    baseplate(spot_temp[p][q].x, spot_temp[p][q].y) = temp;
    // 所铺砖的编号增1, 为下次铺砖准备.
    ++label;
    // 最后平均分割为4块较小尺寸的底板进行递归铺砖.
    DAC(half, {start.x, start.y},
      {spot_temp[0][0].x, spot_temp[0][0].y});
    DAC(half, {start.x, start.y + half},
      {spot_temp[0][1].x, spot_temp[0][1].y});
    DAC(half, {start.x + half, start.y},
      {spot_temp[1][0].x, spot_temp[1][0].y});
    DAC(half, {start.x + half, start.y + half},
      {spot_temp[1][1].x, spot_temp[1][1].y});
  }
}

void LEGO::solve(point init_spot)
{
  // 初始已铺平瓦位置编号为0.
  baseplate(init_spot.x, init_spot.y) = 0;
  label = 1;
  DAC(length, {0, 0}, {init_spot.x, init_spot.y});
}

void LEGO::print(int width)
{
  for (size_t i = 0; i < length; ++i)
  {
    for (size_t j = 0; j < length; ++j)
      std::cout << std::setw(width) << baseplate(i, j);
    std::cout << std::endl;
  }
}
