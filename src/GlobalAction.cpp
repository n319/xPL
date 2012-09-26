#include <vector>
#include <string>
#include <iostream>

#include "GlobalAction.h"
#include "XPLHal.h"
#include <syslog.h>

using namespace std;


GlobalAction::GlobalAction(string namein, string globalNameIn, string globalValueIn)
{
    display_name = namein;
    globalName = globalNameIn;
    globalValue = globalValueIn;
}

GlobalAction::GlobalAction(pugi::xml_node actionnode)
{
 
    bool failed = false;
    
    if (actionnode.attribute("display_name")) {
        display_name = actionnode.attribute("display_name").as_string();
    } else {
        failed = true;
    }
    if (actionnode.attribute("executeOrder")) {
        executeOrder = actionnode.attribute("executeOrder").as_int();
    } else {
        failed = true;
    }
    if (actionnode.attribute("name")) {
        globalName = (actionnode.attribute("name").as_string());
        cout << "name " << globalName << std::endl;
    } else {
        failed = true;
    }
    if (actionnode.attribute("value")) {
        globalValue = (actionnode.attribute("value").as_string());
        cout <<"value " << globalValue << std::endl;
    } else {
        failed = true;
    }
}

GlobalAction::~GlobalAction()
{
  //cout << "deleting logaction: " << this << "\n";
}

//Method to execute the determinator.
//@return returns a vector of XPLMessages for the xPLStack to send out
//on the network.
void GlobalAction::execute(DeterminatorEnvironment* env)
{
    cout << "global action: " << globalName << " = " << globalValue << std::endl;
    XPLHal::instance().globals.setGlobal(globalName, globalValue);
}


// Compares action objects based on the attributes of their contained messages.
// @return true if equal.
bool GlobalAction::equals(GlobalAction* other)
{
  if((globalName == other->globalName)
      && (globalValue == other->globalValue)
      && (executeOrder == other->executeOrder)
      && (display_name == other->display_name))
  {
        return true;
  }
  return false;
}

void GlobalAction::appendAction(pugi::xml_node* outputnode) {

    pugi::xml_node actionnode = outputnode->append_child("globalAction");
    cout << "name " << globalName << std::endl;
    cout << "value " << globalValue << std::endl;
    actionnode.append_attribute("display_name") = display_name.c_str();
    actionnode.append_attribute("executeOrder") = executeOrder;
    actionnode.append_attribute("name") = globalName.c_str();
    actionnode.append_attribute("value") = globalValue.c_str();
    
 }
 