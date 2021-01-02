#include "book.h"

#ifndef LEGO_CLASS
#define LEGO_CLASS

class LEGO {
public:
	LEGO(int N, int init_spot_x, int init_spot_y);
	// 构造函数.
	void Solve();
	// 求解.
	void Output();
	// 在屏幕上输出解法.
private:
	void SolveLEGO(int N, int start_x, int start_y, 
		int spot_x, int spot_y);
	// N为所求解底板当前边长, start_x和start_y为该底板左上角坐标,
	// spot_x和spot_y为当前底板中已铺的位置.
	matrix<int> baseplate;			// 存储底板编号数据的矩阵.
	int init_spot_x, init_spot_y;	// 初始已铺平瓦的位置坐标.
	int length;						// 底板长度.
	int label;						// 编号, 为新铺砖标记编号且不断增加.
};

#endif