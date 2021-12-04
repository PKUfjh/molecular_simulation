#include <random>
#include <chrono>
#include <iostream>
#include <cmath>
 
int main(void) {
  // 从epoch（1970年1月1日00:00:00 UTC）开始经过的纳秒数，unsigned类型会截断这个值
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  
  std::default_random_engine generator(seed);
  // 第一个参数为高斯分布的平均值，第二个参数为标准差
  std::normal_distribution<double> normal(0.0, 1.0);
  std::uniform_real_distribution<double> uniform(0.0,1.0);
 
  std::cout << pow(10,2);
}