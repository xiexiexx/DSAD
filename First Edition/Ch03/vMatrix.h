#include <vector>

#ifndef V_MATRIX
#define V_MATRIX

template <typename T>
class matrix {
public:
	// 构造函数.
	explicit matrix(size_t p = 0, size_t q = 0, const T& initVal = T());
	// 矩阵(i, j)位置的元素.
	T& operator()(size_t i, size_t j);
	// 矩阵(i, j)位置的元素, 常量版本.
	const T& operator()(size_t i, size_t j) const;
	// 返回矩阵的行数.
	size_t dimX() const
	{
		return nRows;
	}
	// 返回矩阵的列数.
	size_t dimY() const
	{
		return nCols;
	}
private:
	// 内部实现是一个向量的向量, 
	// 有兴趣的读者可测试sizeof(vector<T>)的值并思考.
	std::vector<std::vector<T>> mat;
	// 矩阵的行数.
	size_t nRows;
	// 矩阵的列数.
	size_t nCols;
};

// 构造函数实现.
template <typename T>
matrix<T>::matrix(size_t p, size_t q, const T& initVal)
	: mat(p), nRows(p), nCols(q)
{
	for (size_t i = 0; i < p; i++)
	{
		mat[i].resize(q);
		for (size_t j = 0; j < q; j++)
			mat[i][j] = initVal;
	}
}

// 矩阵(i, j)位置的元素.
template <typename T>
T& matrix<T>::operator()(size_t i, size_t j)
{
	return mat[i][j];
}

// 矩阵(i, j)位置的元素, 常量版本.
template <typename T>
const T& matrix<T>::operator()(size_t i, size_t j) const
{
	return mat[i][j];
}

#endif	// V_MATRIX
