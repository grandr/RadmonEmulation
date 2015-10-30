#ifndef  DIMHANDLER_H
#define DIMHANDLER_H

#include <string>
#include <iostream>
#include <dic.hxx>
#include <time.h>
#include <sys/time.h>

#include "DIM_Structures.h"
#include "dimServices.h"


using namespace std;

class  DimHandler  : public DimInfo
{
         
public:
//     DimHandler(string serviceName)  :  DimInfo(serviceName.c_str(),-1)  { infoServiceName = serviceName.c_str(); }
    
    DimHandler(string);
    void infoHandler();
 
private:
    string infoServiceName;
 
    radmon_data_t *rmData;
    void processData();
    void getDeltaT(int&, int&);
    

};
#endif
 