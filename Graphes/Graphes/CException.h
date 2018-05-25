#ifndef C_EXCEPTION
#define C_EXCEPTION 0

#include <string>

using namespace std;

class CException {

private:

	// Attributes
	unsigned int uiEXCValue;
	string sEXCMessage;

public:

	//Constructors
	CException();
	CException(string sMessage);
	CException(unsigned int uiParam, string sMessage);

	//Destructuor
	~CException() {}

	// Methods
	unsigned int EXCgetValue();
	void EXCChangeValue(unsigned int uiParam);
	string EXCgetMessage();
	void EXCDisplay();
};

#endif