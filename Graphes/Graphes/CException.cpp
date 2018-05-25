#include "CException.h"
#include <cstdio> 
#include <iostream>

using namespace std;

CException::CException() {

	uiEXCValue = 0;
	sEXCMessage = nullptr;
}

CException::CException(unsigned int uiParam, string sMessage) {

	sEXCMessage = sMessage;
	uiEXCValue = uiParam;
}

CException::CException(string sMessage) {

	sEXCMessage = sMessage;
}

unsigned int CException::EXCgetValue() {

	return uiEXCValue;
}

void CException::EXCChangeValue(unsigned int uiParam) {

	uiEXCValue = uiParam;
}

string CException::EXCgetMessage() {

	return sEXCMessage;
}

void CException::EXCDisplay() {

	cout << "Exception " << EXCgetValue() << " levee : " << EXCgetMessage() << endl;
}