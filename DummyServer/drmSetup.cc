#include "drmSetup.h"
int DrmSetup::readParameters() 
{
  string key, value;
  ifstream f;
  f.open(configFile.c_str());
  
  if (f.fail()) {
    cout << " Error: cannot open config file" << endl;
    return -1;
  }
  
  while (!f.eof()) {
    f >> key >> value;
    
    if (!f.fail()) {
      parameters[key] = value;
    } 
    else {
      f.clear();
    }
    f.ignore (999, '\n');
  }
  
  return 0;
}

void DrmSetup::getParameters(std::map<string, string> &pars)
{
    pars = parameters;
}

int  DrmSetup::getWeights (vector<double> &weights)
{
  string file = parameters["weights"];
  ifstream f;
  int ndetectors = 0;
  
  f.open (file.c_str());
  if (f.fail()) {
    cout << " Error: cannot open file with the list of weights: " <<  file  << endl;
    return -1;
  }
  double w1, w2, w3, w4; // Four in a row
  
  while (!f.eof()) {
    f >> w1 >> w2 >> w3 >> w4; 
    
    if (!f.fail()) {
      weights.push_back(w1);
      ndetectors++;
      weights.push_back(w2);
      ndetectors++;
      weights.push_back(w3);
      ndetectors++;
      weights.push_back(w4);
      ndetectors++;
    }
    else {
      f.clear();
    }
    f.ignore(999, '\n');
  }
  f.close();
  f.clear();
  if (ndetectors == 0) {
    cout << "No data found" << endl;
    ndetectors = -1;
  }
  return ndetectors;
}


int  DrmSetup::getStatus (vector<unsigned short> &status)
{
  string file = parameters["status"];
  ifstream f;
  int ndetectors = 0;
  
  f.open (file.c_str());
  if (f.fail()) {
    cout << " Error: cannot open file with status: " <<  file  << endl;
    return -1;
  }
  string s; // One status per row
  
  while (!f.eof()) {
    f >> s; 
    
    if (!f.fail()) {
      //Convert to integer
      unsigned short st = bitset<numeric_limits<unsigned short>::digits>(s).to_ulong(); 
      status.push_back(st);
      ndetectors++;
    }
    else {
      f.clear();
    }
    f.ignore(999, '\n');
  }
  f.close();
  f.clear();
  if (ndetectors == 0) {
    cout << "No status data found" << endl;
    ndetectors = -1;
  }
  return ndetectors;
}

string DrmSetup::getMessage ()
{
  string file = parameters["log"];
  ifstream f;
  string message;

//   int nlines = 0;
  
  f.open (file.c_str());
  if (f.fail()) {
    cout << " Error: cannot open file with message: " <<  file  << endl;
    return NULL;
  }
  getline (f,message);
  f.close();
  
  return message;
}

int DrmSetup::oldGetStatus (int &status)
{
  string file = parameters["status"];
  ifstream f;
  f.open (file.c_str());
  if (f.fail()) {
    cout << " Error: cannot open file with status: " <<  file  << endl;
    return -1;
  }
  
  string stringstatus(""), s1, s2, s3, s4;
  while (!f.eof()) {
    f >> s1 >> s2 >> s3 >> s4; 
    if (!f.fail() && s1.find("#") != 0) {
      stringstatus = stringstatus + s4 + s3 + s2 +s1;
    }
    else {
      f.clear();
    }
    f.ignore(999, '\n');
  }
  f.close();
  f.clear();
  
  status = strtol(stringstatus.c_str(), NULL, 2);
  
  return 0;
}

