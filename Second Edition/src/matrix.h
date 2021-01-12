#include <vector>

#ifndef VMATRIX
#define VMATRIX

template <typename T>
class matrix {
public:
	// 构造函数.
	explicit matrix(size_t p = 0, size_t q = 0, const T& value = T());
	// 矩阵(i, j)位置的元素.
	T& operator()(size_t i, size_t j);
	// 矩阵(i, j)位置的元素, 常量版本.
	const T& operator()(size_t i, size_t j) const;
	// 返回矩阵的行数.
	size_t xsize() const
	{
		return nrows;
	}
	// 返回矩阵的列数.
	size_t ysize() const
	{
		return ncols;
	}
private:
	// 内部实现是一个向量的向量, 
	// 有兴趣的读者可测试sizeof(vector<T>)的值并思考.
	std::vector<std::vector<T>> M;
	// 矩阵的行数.
	size_t nrows;
	// 矩阵的列数.
	size_t ncols;
};

// 构造函数实现.
template <typename T>
matrix<T>::matrix(size_t p, size_t q, const T& value)
	: M(p), nrows(p), ncols(q)
{
	for (size_t i = 0; i < p; i++)
		M[i].resize(q, value);
}

// 矩阵(i, j)位置的元素.
template <typename T>
T& matrix<T>::operator()(size_t i, size_t j)
{
	return M[i][j];
}

// 矩阵(i, j)位置的元素, 常量版本.
template <typename T>
const T& matrix<T>::operator()(size_t i, size_t j) const
{
	return M[i][j];
}

#endif	// VMATRIX
