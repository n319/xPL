#ifndef Determinator_H
#define Determinator_H

#include "XPLAction.h"
#include "XPLCondition.h"
#include "XPLMessage.h"

#include <vector>

using namespace std;

class Determinator {
	public:
		Determinator(XPLCondition* condition, XPLAction* action);
		~Determinator();
		bool match(XPLMessage* message);
		vector<XPLMessage> execute();
		void setEnabled(bool enable);
		bool isEnabled();
        void setAction(XPLAction* action);

	protected:
		XPLCondition* getCondition();
		XPLAction* getAction();

	private:
		XPLCondition* condition_;
		XPLAction* action_;
		bool enabled_;
};

#endif //Determinator_H
