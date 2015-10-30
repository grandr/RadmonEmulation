#ifndef DRMSETUP_H
#define DRMSETUP_H

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>
#include <bitset>
#include <limits>

using namespace std;

const string configFile = "dummyRadmon.conf";

class DrmSetup
{
public:
  DrmSetup() {}
  int readParameters();
  string getParameter(string key) {return parameters[key];}
  int getWeights(vector<double> &weights);
  int oldGetStatus(int &status);
  int getStatus(vector<unsigned short> &status);
  string getMessage();
  void getParameters(std::map<string, string> &);

  
  
private:
  std::map<string, string> parameters;
};
#endif
