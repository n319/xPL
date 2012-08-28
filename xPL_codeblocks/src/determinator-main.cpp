// xPL Linux Hal Server
#define HAL_VERSION "1.0"

#define CONFIG_FILE "xHCP.config"

#include "projconfig.h"

#include <string>
#include <stdio.h>
#include <vector>
#include <pthread.h>
#include <signal.h>
#include <syslog.h>
#include <iostream>
#include <fstream>
#include "XPLHal.h"
#include "XPLMessage.h"
#include "XPLParser.h"
#include "XPLRuleManager.h"
#include "Determinator.h"
#include "XPLAction.h"
#include "XPLCondition.h"

/******************************************************************************/
/* Include header files for TCPServer and StreamerThread classes.             */
/******************************************************************************/
#include "TCPDaemon.h"

extern "C" {

    #include "xPLLib/xPL.h"

}

//Prototypes
void* xHCPService(void*);
vector<Determinator>* createDeterminator();

pthread_t xHCP_thread;
xPL_ServicePtr theService = NULL;
XPLRuleManager* ruleMgr;

int main(int argc,const char * argv[])
{
    //fprintf(stderr, "Starting up %d.%d \n", xplhallite_VERSION_MAJOR, xplhallite_VERSION_MINOR);
    fprintf(stderr, "Starting up %d.%d \n", 1, 1);
    openlog("xplhallite", LOG_PID, LOG_DAEMON);

    pthread_create(&xHCP_thread,NULL,&xHCPService, NULL);

    syslog(LOG_INFO, "Main Thread Created.");

    //Load XML document

    //Initialize RuleManager object with returned vector of determinators
//	vector<Determinator>* determinators = new vector<Determinator>();
//	Determinator* determinator = createDeterminator();
//	determinators->push_back(*determinator);
    vector<Determinator>* determinators = createDeterminator();

    ofstream myfile;
    myfile.open ("/tmp/loadedDeterminators.xml");
    
    for(vector<Determinator>::iterator dit = determinators->begin(); dit!=determinators->end(); ++dit) {
        myfile << (*dit).printXML();
    }
    myfile.close();
    
    
	ruleMgr = new XPLRuleManager(determinators);

    //Source Address
    const std::string srcVendor = "HAL9000";
    const std::string srcDeviceID = "xPLHAL";
    const std::string srcInstanceID = "1";

    /* Start xPL up */
    if (!xPL_initialize(xPL_getParsedConnectionType())) {
        fprintf(stderr, "Unable to start xPL");
        exit(1);
    }

    /* And a listener for all xPL messages */
    xPL_addMessageListener(XPLParser::recvMsg, NULL);

    /* Create a service so the hubs know to send things to us        */
    /* While we are not really using the service, xPL hubs will not  */
    /* forward messages to us until they have seen an xPL-looking    */
    /* device on the end of a hub connection. So this just gets us a */
    /* place at the table, so to speak                               */
    theService = xPL_createConfigurableService(srcVendor.c_str(), srcDeviceID.c_str(), "hal.xpl");
    //theService = xPL_createConfigurableService(srcVendor.c_str(),"b", "hal.xpl");
    xPL_setServiceVersion(theService, HAL_VERSION);

    xPL_setServiceEnabled(theService, TRUE);

    /* Hand control over to xPLLib */
    /* Main thread is processing xPL messages */
    /* xHCP_thread is processing xHCP messages */
    xPL_processMessages(-1);

    pthread_join(xHCP_thread,NULL);

	closelog();
    return 0;
}

//The xHCP thread executes this function
void* xHCPService(void*)
{
    Daemon cDaemon(CONFIG_FILE);

    cDaemon.RunDaemon();
}

vector<Determinator>* createDeterminator()
{
	//First, let's create the condition
	XPLAddress conditionAddress;
	XPLSchema conditionSchema;
	string conditionMsgType;

	XPLValuePair pairOne, pairTwo;
	pairOne.member = "device";
	pairOne.value = "button2";
	pairTwo.member = "current";
	pairTwo.value = "HIGH";

	vector<XPLValuePair>* conditionVector = new vector<XPLValuePair>();
	conditionVector->push_back(pairOne);
	conditionVector->push_back(pairTwo);


  conditionSchema.schema = "control";
  conditionSchema.type = "basic";
  
	XPLCondition* condition = new XPLCondition(conditionVector, conditionAddress, conditionAddress, conditionSchema, 5, conditionMsgType );

    //Create the actions
    XPLMessage turnLampOn;
    turnLampOn.setMsgType("xpl-cmnd");
    turnLampOn.setSource("XPLHal", "XPLHal", "XPLHal");
    turnLampOn.setDestination("smgpoe", "lamp", "1");
    turnLampOn.setSchema("control", "basic");
    turnLampOn.setHops(5);
    turnLampOn.setBroadcast(false);
    turnLampOn.addMember("device", "pwm");
    turnLampOn.addMember("type", "variable");
    turnLampOn.addMember("current", "200");

	vector<XPLMessage>* actionVector = new vector<XPLMessage>();
	actionVector->push_back(turnLampOn);

	XPLAction* action = new XPLAction(actionVector);

    //Create a determinator with the condition and action created above
	Determinator* determinator1 = new Determinator(condition, action);


	//First, let's create the condition
	XPLValuePair pairThree, pairFour;
	pairThree.member = "device";
	pairThree.value = "button1";
	pairFour.member = "current";
	pairFour.value = "HIGH";

	vector<XPLValuePair>* conditionVector2 = new vector<XPLValuePair>();
	conditionVector2->push_back(pairThree);
	conditionVector2->push_back(pairFour);

	XPLCondition* condition2 = new XPLCondition(conditionVector2, conditionAddress, conditionAddress, conditionSchema, 5, conditionMsgType);

    //Create the actions
    XPLMessage turnLampOn2;
    turnLampOn2.setMsgType("xpl-cmnd");
    turnLampOn2.setSource("XPLHal", "XPLHal", "XPLHal");
    turnLampOn2.setDestination("smgpoe", "lamp", "1");
    turnLampOn2.setSchema("control", "basic");
    turnLampOn2.setHops(5);
    turnLampOn2.setBroadcast(false);
    turnLampOn2.addMember("device", "pwm");
    turnLampOn2.addMember("type", "variable");
    turnLampOn2.addMember("current", "0");

	vector<XPLMessage>* actionVector2 = new vector<XPLMessage>();
	actionVector2->push_back(turnLampOn2);

	XPLAction* action2 = new XPLAction(actionVector2);

    //Create a determinator with the condition and action created above
	Determinator* determinator2 = new Determinator(condition2, action2);
  

	vector<Determinator>* determinators = new vector<Determinator>();;
	determinators->push_back(*determinator1);
	determinators->push_back(*determinator2);

	return determinators;
}