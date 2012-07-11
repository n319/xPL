#include "DeterminatorFactory.h"
#include "XPLAction.h"
#include "XPLCondition.h"
#include <string>
#include <vector>

DeterminatorFactory::DeterminatorFactory()
{
}

DeterminatorFactory::~DeterminatorFactory()
{
}

string DeterminatorFactory::getMember(string definition)
{
	int splitIndex = definition.find_first_of("=");
	definition = definition.substr(0, splitIndex);
	return definition;
}

string DeterminatorFactory::getValue(string definition)
{
	int splitIndex = definition.find_first_of("=");
	definition = definition.substr(splitIndex+1, definition.length());
	return definition;	
}

Determinator* DeterminatorFactory::createDeterminator(string definitions[])
{
	Determinator* determinator;	
	if(definitions[0].compare("-determinator") == 0)
	{	
		XPLCondition* condition;
		XPLAction* action;
	}
	return determinator;
}

XPLCondition* DeterminatorFactory::createCondition(string definitions[])
{
	int index = startOfPairs;
	vector<XPLValuePair>* conditionVector = new vector<XPLValuePair>();
	while(!definitions[index].compare("action"))
	{
		XPLValuePair* valuePair = new XPLValuePair(); 
		valuePair->member = getMember(definitions[index]);
	}
}

XPLAction* DeterminatorFactory::createAction(string definitions[])
{
	
}


