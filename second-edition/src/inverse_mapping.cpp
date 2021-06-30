#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

using std::vector;
using std::string;
using std::unordered_map;
using std::ifstream;
using std::ofstream;
using std::cerr;
using std::pair;

int main()
{
  // names是存储名字的向量, 其下标和元素值形成天然的映射.
  vector<string> names;
  // IM是unordered_map<string, size_t>型映射,
  // 键类型是string, 值类型是size_t.
  // IM用于反向查找names中的数据以获得其下标.
  unordered_map<string, size_t> IM;
  ifstream infile("pairs.txt", std::ios::in);
  if (!infile)
  {
    // 打开文件错误则报告.
    cerr << "Error!";
    exit(-1);
  }
  // 存储编号数据对的向量P.
  vector<pair<size_t, size_t>> P;
  string u, v;
  // 不断读取u, 以'\t'作为分隔.
  while(getline(infile, u, '\t'))
  {
    // 接着读取v, 以'\n'作为分隔.
    getline(infile, v, '\n');
    // 在IM中查找u是否存在映射值.
    auto iter = IM.find(u);
    // 若u在IM中没有对应的映射值.
    if (iter == IM.cend())
    {
      // 添加新名字.
      names.push_back(u);
      // 插入键值映射, 其中u为键而names.size() - 1为值.
      IM.insert({u, names.size() - 1});
    }
    // 使用另外一种方法查找IM中是否存在指定的键, 即count成员函数.
    if (IM.count(v) == 0)
    {
      // 若v在IM中没有对应的映射值则放入names.
      names.push_back(v);
      // 在映射中插入数据对的另一种方法:
      // 插入v和names.size() - 1所组成的数据对, 不过要保证v没有映射值.
      // 如果v有映射值, 那么IM[v]代表v的映射值, 注意该值可修改.
      IM[v] = names.size() - 1;
    }
    // 经过处理后, u和v必然都在IM中有对应的映射值IM[u]和IM[v],
    // 将IM[u]和IM[v]所组成的数据对加入P中.
    P.push_back({IM[u], IM[v]});
  }
  // 将键(名字)和值(编号)全部输出到names_numbers.txt文件中.
  ofstream outfile("names_numbers.txt", std::ios::out);
  // 按照名字升序输出. 名字和编号之间以'\t'分隔, 数据对之间以'\n'分隔.
  for (auto iter = IM.cbegin(); iter != IM.cend(); ++iter)
  {
    // iter->first和iter->second分别代表键和值.
    outfile << iter->first << '\t';
    outfile << iter->second << '\n';
  }
  outfile.close();
  // 将编号数据对输出到pairs_out.txt文件中.
  outfile = ofstream("pairs_out.txt", std::ios::out);
  for (size_t i = 0; i < P.size(); ++i)
  {
    // 分别将数据对P[i]的第一个元素和第二个元素输出到文件中.
    outfile << P[i].first << '\t';
    outfile << P[i].second << '\n';
  }
  outfile.close();
  return 0;
}
