#include "CArc.h"

/*************************************
 *** Default constructor           ***
 *** Set the value of the arc at 0 ***
 *** Can't be used by users        ***
 ************************************/
CArc :: CArc() {
	uiARCVertex = 0;
}

/************************
 *** Copy constructor **
 ***********************/
CArc :: CArc(CArc &ARCParam) {
	uiARCVertex = ARCParam.uiARCVertex;
}

/*******************************************************
 *** Constructor setting the arc's destination value ***
 *** E : uiParam the value                           ***
 ******************************************************/
CArc :: CArc(unsigned int uiParam) {
	uiARCVertex = uiParam;
}

/****************************************
 *** Get the arc destination          ***
 *** R : The value of the destiantion ***
 ***************************************/
unsigned int CArc :: ARCgetVertex() {
	return uiARCVertex;
}
