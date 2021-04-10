#include <string>
#include <chrono>
#include <iostream>

using std::string;
using std::stoi;
using std::cout;
using std::endl;
using std::chrono::operator""h;
using std::chrono::operator""min;

int time_duration(const string& S)
{
  // 假定S为HH:MM格式, 取前两位作为小时值而后两位作为分钟值.
  auto d = stoi(S, 0) * 1h + stoi(S.substr(3)) * 1min;
  // 返回从午夜到S的时长, 单位为分钟.
  return d.count();
}

int main()
{
  // 从午夜到06:20共计l(也即380)分钟.
  int l = time_duration("06:20");
  // 从午夜到08:00共计r(也即480)分钟.
  int r = time_duration("08:00");
  // [06:20, 08:00)时长为100分钟.
  cout << r - l << endl;
  return 0;
}
