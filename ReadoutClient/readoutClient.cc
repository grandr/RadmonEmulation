#include <string>
#include <iostream> 
#include <dic.hxx>
#include "DIM_Structures.h"
#include "dimServices.h"
#include "dimhandler.h"
#include "utils.h"

using namespace std;

int toSleep = 1000000;

int main(int argc, char *argv[]) {
    
    struct timeval tp;
    
//     DaqUtils *utl = new DaqUtils();
    string command("HFRADMON_DUMMY/COMMANDS");
    string dnsNode("localhost");
    
    // Services 
    string radmonDataServiceName("HFRADMON_DUMMY/RadmonData");
    
    DimHandler *dimRadmonData = new DimHandler(radmonDataServiceName);
    
    radmon_cmd_t cmdData;
    
    cmdData.command = 0;  	// Publish data 
    cmdData.cmd_arg = 0;  	// Not used
    cmdData.fill = 4495;	// Fill no
    cmdData.runnr = 12345;  // Run no
    cmdData.lumisection = 1;
    cmdData.nibble = 0;
    
    DimClient::setDnsNode(dnsNode.c_str());
    
    for (int i=0; i<24; i++)
    {
	cmdData.data[i] = 0.;
    }		// Not used
  
    while (1) {
	// Make timestamp
	gettimeofday(&tp, NULL);
	cmdData.tstamp = tp.tv_sec;
	cmdData.msec =  static_cast<int>(tp.tv_usec/1000.);
	
// 	cout << cmdData.tstamp  << "\t" <<  cmdData.msecs << endl;
	cmdData.nibble++;
	cmdData.lumisection = int(cmdData.nibble/23.) + 1;
	cout << "====================" << endl;
	cout << "Sending nibble/ls\t" << cmdData.nibble  << "\t" <<  cmdData.lumisection << endl;
	
	int status = DimClient::sendCommand(command.c_str(), (void*) &cmdData, sizeof(cmdData));
	if (status == 0) {
	    cout << "Problem sending command" << endl;
	}
	usleep(toSleep);
    }
    
    return 0;
}
    
    