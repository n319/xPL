#ifndef XPLCondition_H
#define XPLCondition_H

#include "XPLHal.h"
#include "XPLMessage.h"

using namespace std;

class XPLCondition {
	public:
		explicit XPLCondition(vector<XPLValuePair> attributes);
		XPLCondition(XPLCondition condition);
		~XPLCondition();
		bool match(XPLMessage);

	private:
		vector<XPLValuePair> attributes_;		
};

#endif //XPLAction_H
