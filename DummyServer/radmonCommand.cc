#include "radmonCommand.h"
int timeout = 5;
void Command::init()
{
    string rateServiceName = parameters["rateServiceName"];
    string logServiceName = parameters["logServiceName"];
    string stateServiceName = parameters["stateServiceName"];
    
    string radmonDataServiceName = parameters["radmonDataServiceName"];
    
    string serverName = parameters["serverName"];    
    
    rateServiceName = serverName + "/" + rateServiceName;
    logServiceName = serverName + "/" + logServiceName;
    stateServiceName = serverName + "/" + stateServiceName;
// New
    radmonDataServiceName = serverName + "/" + radmonDataServiceName;

    radmonRates = new DimService(rateServiceName.c_str(), rateService, (void*) &ratesMon, atoi(rateLength));
    radmonLog = new DimService(logServiceName.c_str(), logService, (void*) &logMon, atoi(logLength));
    radmonState = new DimService(stateServiceName.c_str(), stateService, (void*) &stateMon, atoi(stateLength));
    radmonData = new DimService(radmonDataServiceName.c_str(), radmonDataService, (void*) &rmData, sizeof(rmData));  

    // Reset everything
    
    for (int i = 0; i < 24; i++) {
	ratesMon.rates[i] = 0.;
	stateMon.adc[i] = 0.;
	stateMon.adc[2*i+1] = 0.;
    }
    
    for (int i=0; i<16; i++) {
	rmData.rate[i] = 0.;
	rmData.voltage[i] = 0.;
	rmData.current[i] = 0.;
	rmData.status[i] = 0;
	rmData.flux[i] = 0;
    }
    rmData.onoff = 0;
    rmData.startup = 0;
    rmData.included = 0;
    rmData.config = 0;
    rmData.tstamp = 0;
    rmData.msec = 0;
    rmData.dt_period = 0;
    rmData.dt_readout = 0;
    rmData.fill = 0;
    rmData.runnr = 0;
    rmData.nibble = 0;
       
    rmData.lumiMinusZ = 0.;
    rmData.lumiPlusZ = 0.;
    rmData.lumiMinusZrms = 0.;
    rmData.lumiPlusZrms = 0.;
    
    
    
    utl = new Utils();
    gRandom->SetSeed();
    brilTs.sec = 0;
    brilTs.msec = 0;
    
    rate_mean = 500.;
    rate_sigma = 20.;
    voltage_mean = 50000.;
    voltage_sigma = 100.;
    
    cmdData = new radmon_cmd_t();
    
    DimTimer::start(timeout);
}

void Command::commandHandler()
{
    cmdData = (radmon_cmd_t*)getData();
    
    switch (cmdData->command) {
	
	case 0:   // readout from BRIL
	{
	    DimTimer::stop();
	    utl->logMessage("BrilDAQ readout request");
	    brilTs.sec = cmdData->tstamp;
	    brilTs.msec = cmdData->msec;
	    doReadout();
	    updateOldServices();
	    updateNewServices();
	    DimTimer::start(timeout);
	    break;
	}   

	default:
	{
	    utl->logMessage("All other commands");
	}
    }
}

void Command::timerHandler()
{
    utl->logMessage("Internal readout ");
    
    // Reset cmdData structure
    utl->getLocalTs(tsCurrent);
    brilTs.sec = tsCurrent.sec;
    brilTs.msec = tsCurrent.msec;   
    cmdData->fill = int(0);
    cmdData->runnr = 0;
    cmdData->lumisection = 0;
    cmdData->nibble = 0;
    doReadout();
    updateOldServices();
    DimTimer::start(timeout);
}

void Command::doReadout()
{
    utl->getLocalTs(tsCurrent);
    ratesMon.tstamp = tsCurrent.sec;
    stateMon.tstamp = tsCurrent.sec;
    rmData.tstamp = tsCurrent.sec;
    rmData.msec = tsCurrent.msec;

    // dt_period & dt_readout to store timestamp from command
    rmData.dt_period = brilTs.sec;
    rmData.dt_readout = brilTs.msec;
    rmData.fill = cmdData->fill;
    rmData.runnr = cmdData->runnr;
    rmData.lumisection = cmdData->lumisection;
    rmData.nibble = cmdData->nibble;
    
    rmData.onoff = 1;
    rmData.startup = 0;
    rmData.included = 1;
    rmData.config = 5;
    
    for (int i=0;i<24;i++) {
	ratesMon.rates[i] = gRandom->Gaus(rate_mean, rate_sigma);
	stateMon.adc[i] = gRandom->Gaus(voltage_mean, voltage_sigma);
	stateMon.adc[2*i+1] = gRandom->Gaus(voltage_mean/2., voltage_sigma/2.);
    }
    for (int i=0;i<16;i++) {
	rmData.rate[i] = ratesMon.rates[i];
	rmData.voltage[i] = stateMon.adc[i];
	rmData.current[i] = stateMon.adc[2*i+1];
	rmData.flux[i] = rmData.rate[i] * 1.5;
    }
    
    float sumPlusZ = 0.;
    float sumMinusZ = 0.;

    for (int i=0; i<4; i++) {
	sumPlusZ += rmData.rate[i];
	sumMinusZ += rmData.rate[i+5];
    }

    rmData.lumiMinusZ = sumMinusZ/4.;
    rmData.lumiPlusZ = sumPlusZ/4.;
    rmData.lumiMinusZrms = rmData.lumiMinusZ/10.;
    rmData.lumiPlusZrms = rmData.lumiPlusZ/10.;
}

void Command::updateOldServices()
{
    radmonRates->updateService();
    radmonState->updateService();
    radmonLog->updateService();
}


void Command::updateNewServices()
{
    usleep(1000);
    radmonData->updateService();
}
