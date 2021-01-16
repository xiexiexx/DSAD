#include <vector>

template <typename T>
void prefixsum(const std::vector<T>& A, std::vector<T>& S)
{
  // 对输入A计算所有部分和, 输出为S.
  S = A;
  for (size_t i = 1; i < A.size(); ++i)
    S[i] += S[i - 1];
  // 尽管也可以使用S[i] = S[i - 1] + A[i];
  // 但由于初始A的值已全复制到S中, 使用一个向量内的运算更好.
}
