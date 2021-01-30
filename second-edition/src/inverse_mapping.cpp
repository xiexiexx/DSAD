#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>
#include <iostream>

using namespace std;

int main()
{
  // names是存储名字的向量, 其下标和元素值形成天然的映射.
  vector<string> names;
  // IM是unordered_map<string, size_t>型映射,
  // 键类型是string, 值类型是size_t.
  // IM用于反向查找names中的数据以获得其下标.
  unordered_map<string, size_t> IM;
  ifstream infile("pairs.txt", ios::in);
  if (!infile)
  {
    // 打开文件错误则报告.
    cerr << "Error!";
    exit(-1);
  }
  // 将names和IM清空.
  names.clear();
  IM.clear();
  // 存储编号数据对的向量.
  vector<pair<size_t, size_t>> PV;
  string u, v;
  while(getline(infile, u, '\t')) // 不断读取u, 以'\t'作为分隔.
  {
    getline(infile, v, '\n');     // 接着读取v, 以'\n'作为分隔.
    auto iter = IM.find(u);       // 在IM中查找u是否存在映射值.
    if (iter == IM.cend())        // 若u在IM中没有对应的映射值.
    {
      names.push_back(u);         // 添加新名字.
      // 插入(u, names.size() - 1)键值映射.
      IM.insert({u, names.size() - 1});
    }
    // 使用另外一种方法查找IM中是否存在指定的键, 即count成员函数.
    if ( IM.count(v) == 0 )       // 若v在IM中没有对应的映射值.
    {
      names.push_back(v);
      // 在映射中插入数据对的另一种方法:
      // 插入数据对(v, names.size() - 1), 不过要保证v没有映射值!
      // 如果v有映射值, IM[v]代表v的映射值, 可以使用这个值也可修改它.
      IM[v] = names.size() - 1;
    }
    // 经过处理后, u和v必然都在IM中有对应的映射值IM[u]和IM[v],
    // 将数据对(IM[u], IM[v])加入PV中.
    PV.push_back({IM[u], IM[v]});
  }
  // 将键(名字)和值(编号)全部输出到names_numbers.txt文件中.
  ofstream outfile("names_numbers.txt", ios::out);
  // 按照名字升序输出. 名字和编号之间以'\t'分隔, 数据对之间以'\n'分隔.
  for (auto iter = IM.cbegin(); iter != IM.cend(); ++iter)
  {
    // iter->first和iter->second分别代表键和值.
    outfile << iter->first << '\t';
    outfile << iter->second << '\n';
  }
  outfile.close();
  // 输出编号数据对到pairs_out.txt文件中.
  outfile = ofstream("pairs_out.txt", ios::out);
  for (size_t i = 0; i < PV.size(); i++)
  {
    // 分别将数据对PV[i]的第一个元素和第二个元素输出到文件中.
    outfile << PV[i].first << '\t';
    outfile << PV[i].second << '\n';
  }
  outfile.close();
  return 0;
}
