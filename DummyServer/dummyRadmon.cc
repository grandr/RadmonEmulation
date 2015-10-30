#include <iostream>
#include <dis.hxx>
#ifndef WIN32
#include <unistd.h>
#endif

using namespace std;

#include <string>
#include <time.h>

#include "drmSetup.h"
#include "radmonCommand.h"
#include "DIM_Structures.h"
#include "dimServices.h"

int main()
{
  
    DrmSetup *setupData = new DrmSetup();
  

    if (setupData->readParameters()) exit(-1);
    string serverName = setupData->getParameter("serverName");
    string dimCommandName = setupData->getParameter("dimCommandName");
    string dnsNode = setupData->getParameter("dnsNode");

    dimCommandName =  serverName + "/" + dimCommandName;
  
    Command dimCommand(dimCommandName, (char*) &commandStructure);
    std::map<string, string> pars;
    setupData->getParameters(pars);
    dimCommand.setParameters(pars);
    dimCommand.init();
    
    DimServer::setDnsNode(dnsNode.c_str());
    DimServer::start(serverName.c_str());
  
    while(1) {
	pause();
    }
    return 0;
}
