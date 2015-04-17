#ifndef _Random_H
#define _Random_H

#include<cstdlib>
#include<ctime>
#include<cmath>

using std::srand;
using std::time;
using std::rand;
using std::abs;

class Random
{
public:
  static int seeded;
  Random(void);
  Random(float, float);

  float operator()(void);

private:
  void seed(void);

  float min_;
  float max_;
};
#endif