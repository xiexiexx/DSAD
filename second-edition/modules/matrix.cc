export module matrix;

import <vector>;

export
template <typename T>
class matrix {
public:
  // 构造函数.
  explicit matrix(size_t p = 0, size_t q = 0, const T& value = T())
    : M(p), n_rows(p), n_cols(q)
  {
    for (size_t i = 0; i < p; ++i)
      M[i].resize(q, value);
    // 也可换用M(p, std::vector<T>(q, value))构造.
  }

  // 矩阵(i, j)位置的元素.
  T& operator()(size_t i, size_t j)
  {
    return M[i][j];
  }

  // 矩阵(i, j)位置的元素, 常量版本.
  const T& operator()(size_t i, size_t j) const
  {
    return M[i][j];
  }

  // 返回矩阵的行数.
  size_t x_size() const
  {
    return n_rows;
  }

  // 返回矩阵的列数.
  size_t y_size() const
  {
    return n_cols;
  }

private:
  // 内部实现是一个向量的向量, 也即M.
  // 有兴趣的读者可测试sizeof(vector<T>)的值并思考.
  std::vector<std::vector<T>> M;
  // 矩阵的行数.
  size_t n_rows;
  // 矩阵的列数.
  size_t n_cols;
};
;
