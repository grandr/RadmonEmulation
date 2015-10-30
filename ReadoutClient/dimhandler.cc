#include "dimhandler.h"

DimHandler::DimHandler(string serviceName) : DimInfo(serviceName.c_str(),-1)  
{ 
    rmData = new radmon_data_t();
    infoServiceName = serviceName.c_str(); 
}

void DimHandler::infoHandler() 
{

//     cout << "In infoHandler" << endl;
    if ( getName() == infoServiceName)
    {
	processData();
    }

}

void DimHandler::processData()
{
    rmData = (radmon_data_t*)getData();
    cout << "Nibble/ls received: " << rmData->nibble << "\t" << rmData->lumisection << endl;
    int delta1, delta2;
    getDeltaT(delta1, delta2);
    cout << "TS difference:\tServer-Command=" << delta1 << "\t" << "Received-Command=" << delta2 << endl;
//     cout << "lumi data  +Z:" << rmData->lumiPlusZ << "\t-Z:" << rmData->lumiMinusZ<< endl;
}

void DimHandler::getDeltaT(int &delta1, int &delta2)
{
//     Difference between timestamps (command sent, server response, response obtained)
    double fromServer = 1.*rmData->tstamp + rmData->msec/1000.;
    double fromCommand = rmData->dt_period*1. + rmData->dt_readout/1000.;
    
    struct timeval vv;
    gettimeofday(&vv, NULL);
    double currentTs = (double)vv.tv_sec + vv.tv_usec/1e06;
    
    delta1 = (fromServer - fromCommand) * 1000.;
    delta2 = (currentTs - fromCommand) * 1000.;
    return;
}
    
    
	 
	 