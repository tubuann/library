#ifndef time_hpp
#define time_hpp

#include<bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;
typedef long long int ll;
#define F first
#define S second

chrono::system_clock::time_point Start,End;

void start(){Start=chrono::system_clock::now();}

double end(){
  End=chrono::system_clock::now();
  double diff=chrono::duration_cast<chrono::milliseconds>(End-Start).count();
  return diff;
}

#endif /*time_hpp*/
