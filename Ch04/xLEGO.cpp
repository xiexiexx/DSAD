#include "xLEGO.h"
#include "book.h"

LEGO::LEGO(int N, int given_spot_x, int given_spot_y)
	: baseplate(N, N, -1), length(N),
		init_spot_x(given_spot_x), init_spot_y(given_spot_y) 
{
	// 初始已铺平瓦位置编号为0.
	baseplate(init_spot_x, init_spot_y) = 0;
}

void LEGO::SolveLEGO(int N, int start_x, int start_y, 
	int spot_x, int spot_y)
{
	if (N > 1)
	{
		int half = N / 2;
		int i, j;
		// spot_x_temp和spot_y_temp描述更小底板的已铺位置坐标.
		int spot_x_temp[2][2];
		int spot_y_temp[2][2];
		// 先统一给出中心位置4个点的坐标, 也可用for语句实现(但稍慢).
		spot_x_temp[0][0] = start_x + half - 1;
		spot_y_temp[0][0] = start_y + half - 1;
		spot_x_temp[0][1] = start_x + half - 1;
		spot_y_temp[0][1] = start_y + half;
		spot_x_temp[1][0] = start_x + half;
		spot_y_temp[1][0] = start_y + half - 1;
		spot_x_temp[1][1] = start_x + half;
		spot_y_temp[1][1] = start_y + half;
		// 再将中心位置4个点中不需要铺砖的位置为真正的已铺位置.
		int p = (spot_x - start_x) / half;
		int q = (spot_y - start_y) / half;
		spot_x_temp[p][q] = spot_x;
		spot_y_temp[p][q] = spot_y;
		// 暂时保存不需要铺砖的位置原有的值.
		int temp = baseplate(spot_x_temp[p][q], spot_y_temp[p][q]);
		// 对中心位置进行一次铺砖操作
		baseplate(spot_x_temp[0][0], spot_y_temp[0][0]) = label;
		baseplate(spot_x_temp[0][1], spot_y_temp[0][1]) = label;
		baseplate(spot_x_temp[1][0], spot_y_temp[1][0]) = label;
		baseplate(spot_x_temp[1][1], spot_y_temp[1][1]) = label;
		// 恢复不需要铺砖的位置原有的值, 此方式避免了判断语句.
		baseplate(spot_x_temp[p][q], spot_y_temp[p][q]) = temp;
		// 所铺砖的编号增1, 为下次铺砖准备.
		label++;
		// 最后平均分割为4块较小尺寸的底板进行递归铺砖.
		SolveLEGO(half, start_x, start_y,
			spot_x_temp[0][0], spot_y_temp[0][0]);
		SolveLEGO(half, start_x, start_y + half,
			spot_x_temp[0][1], spot_y_temp[0][1]);
		SolveLEGO(half, start_x + half, start_y,
			spot_x_temp[1][0], spot_y_temp[1][0]);
		SolveLEGO(half, start_x + half, start_y + half,
			spot_x_temp[1][1], spot_y_temp[1][1]);
	}
}

void LEGO::Solve()
{
	label = 1;
	SolveLEGO(length, 0, 0, init_spot_x, init_spot_y);
}

void LEGO::Output()
{
	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
			cout << setw(5) << baseplate(i, j);
		cout << endl;
	}
}