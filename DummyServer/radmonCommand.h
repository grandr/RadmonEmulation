#ifndef  RADMONCOMMAND_H
#define RADMONCOMMAND_H
#include <dis.hxx>
#include <dim.hxx>
#include "DIM_Structures.h"
#include "dimServices.h"
#include <string>
#include <iostream>
#include <map>
#include "utils.h"
#include <TRandom.h>

using namespace std;

class Command : public DimCommand , public DimTimer
{
public:

    Command(string name, char *format) : DimCommand(name.c_str(), format) , DimTimer() {};
    void init();
    void setParameters(std::map<string,string> p) { parameters = p; }
    
    
private:
    Rate ratesMon;
    State stateMon;
    Log logMon;
    //   New stuff
    radmon_cmd_t *cmdData;
    radmon_data_t rmData;  
    //=====
    
    std::map<string, string> parameters;
    
    DimService *radmonRates;
    DimService *radmonLog;
    DimService *radmonState;
    
    DimService *radmonData;
    
    void timerHandler();
    void commandHandler();
    
    Utils *utl;
    
    TimeStamp brilTs;
    TimeStamp tsCurrent;
    void doReadout();
    void updateOldServices();
    void updateNewServices();
    
    // Junk for emulation
    float rate_mean;
    float rate_sigma;
    float voltage_mean; 
    float voltage_sigma;
    
    
};

#endif