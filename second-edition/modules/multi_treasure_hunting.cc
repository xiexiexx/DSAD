export module multi_treasure_hunting;

import <vector>;
import <string>;
import <set>;
import <iostream>;

using std::vector;
using std::string;
using std::multiset;
using std::cout;
using std::endl;

export void multi_treasure_hunting(const vector<vector<string>>& H,
                                   const vector<string>& F)
{
  if (F.empty())
    return;
  // 存放待查宝物的多重集合S.
  multiset<string> S;
  // 使用移动语义将宝物逐个转存并插入多重集合S中.
  std::move(F.begin(), F.end(), std::inserter(S, S.end()));
  for (size_t i = 0; i < H.size(); ++i)
  {
    for (size_t j = 0; j < H[i].size(); ++j)
    {
      // 寻找山洞H[i]中的第j件宝物.
      auto iter = S.find(H[i][j]);
      if (iter != S.end())
      {
        cout << "Find " << *iter << endl;
        // 在待查宝物清单中删除所找到的宝物.
        iter = S.erase(iter);
        // 不必再在本山洞中寻找. 也可直接以S.erase(H[i][j])返回值判定.
        break;
      }
    }
    // 已无宝物, 则可终止.
    if (S.empty())
      return;
  }
}
