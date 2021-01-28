#include <vector>
#include <multiset>

using std::vector;
using std::multiset;

void TreasureHunting(const vector<vector<int>>& H, const vector<int>& F)
{
  // 存放待找宝物的多重集合S.
  multiset<int> S;
  // 将宝物逐个加入多重集合S中.
  for (size_t i = 0; i < F.size(); i++)
    S.insert( F[i] );
  for (size_t i = 0; i < H.size(); i++)
  {
    // 若已无宝物可找则终止.
    if (S.empty())
      return;
    // 未退出则意味着仍有宝物可找.
    for (size_t j = 0; j < H[i].size(); j++)
    {
      // 寻找山洞H[i]中的第j件宝物.
      auto iter = S.find( H[i][j] );
      if (iter != S.end())
      {
        cout << "Find " << *iter << endl;
        // 在待找宝物清单中删除所找到的宝物.
        iter = S.erase(iter);
        // 不必再在本山洞中寻找.
        break;
      }
    }
  }
}