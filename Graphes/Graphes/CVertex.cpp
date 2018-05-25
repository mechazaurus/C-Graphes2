#include "CException.h"
#include "CVertex.h"

/***************************************
*** Default constructor              ***
*** Set the value of the vertex at 0 ***
*** Can't be used by users           ***
***************************************/
CVertex :: CVertex() {
	uiVERNumber = 0;
}

/***********************
*** Copy constructor ***
***********************/
//Different
CVertex :: CVertex(const CVertex &VERParam) {

	uiVERNumber = VERParam.VERgetVertexNumber();

	unsigned int uiIncomingVectorSize = VERParam.VERgetIncomingVectorSize();
	unsigned int uiOutcomingVectorSize = VERParam.VERgetOutcomingVectorSize();

	for (unsigned int uiLoop = 0 ; uiLoop < uiIncomingVectorSize ; uiLoop++) {
		vVERIncomingArcs.push_back(new CArc(VERParam.VERgetIncomingArcDestination(uiLoop)));
	}

	for (unsigned int uiLoop = 0; uiLoop < uiOutcomingVectorSize ; uiLoop++) {
		vVEROutcomingArcs.push_back(new CArc(VERParam.VERgetOutcomingArcDestination(uiLoop)));
	}
}
/**********************************************
*** Constructor setting the vertex's number ***
*** E : uiParam the value                   ***
**********************************************/
CVertex :: CVertex(unsigned int uiParam) {
	uiVERNumber = uiParam;
}

/*********************************
*** Destructor - Free the arcs ***
*********************************/
CVertex :: ~CVertex() {
	
	for (unsigned int uiLoop = 0 ; uiLoop < vVERIncomingArcs.size() ; uiLoop++) {
		delete(vVERIncomingArcs[uiLoop]);
	}

	vVERIncomingArcs.clear();

	for (unsigned int uiLoop = 0 ; uiLoop < vVEROutcomingArcs.size() ; uiLoop++) {
		delete(vVEROutcomingArcs[uiLoop]);
	}

	vVEROutcomingArcs.clear();
}

/*******************************
 *** Get the vertex's number ***
 *** R: the vertex's number  ***
 ******************************/
unsigned int CVertex :: VERgetVertexNumber() const {
	return uiVERNumber;
}



// Manipulations of incoming arcs

/***********************************************
*** Get the size of the incoming arcs vector ***
*** R : the size of the vector               ***
***********************************************/
unsigned int CVertex :: VERgetIncomingVectorSize() const {
	return vVERIncomingArcs.size();
}

/********************************************************************************
 *** Get the arc's destination value from the incoming vector at the position ***
 *** E : uiIndex the position                                                 ***
 *******************************************************************************/
unsigned int CVertex :: VERgetIncomingArcDestination(unsigned int uiIndex) const {
	return vVERIncomingArcs[uiIndex]->ARCgetVertex();
}

/*******************************************
*** Add an arc to the incoming arcs list ***
*** E : ARCParam the arc to add          ***
*******************************************/
void CVertex :: VERaddIncomingArc(CArc *ARCParam) {

	if (ARCParam->ARCgetVertex() == uiVERNumber) {
		throw CException(C_VERTEX_ITSELF, "Un sommet ne peut pas pointer vers lui-meme");
	}

	unsigned int uiIncomingVectorSize = vVERIncomingArcs.size();

	for (unsigned int uiLoop = 0 ; uiLoop < uiIncomingVectorSize ; uiLoop++) {

		if (vVERIncomingArcs[uiLoop]->ARCgetVertex() == ARCParam->ARCgetVertex()) {
			throw CException(C_VERTEX_ARC_ALREADY_EXISTS, "L'arc existe deja dans la liste des arcs entrants");
		}
	}

	vVERIncomingArcs.push_back(ARCParam);
}

/**************************************************
*** Delete an arc from the incoming arcs vector ***
*** E : The arc to delete                       ***
**************************************************/
void CVertex :: VERdeleteIncomingArc(CArc *ARCParam) {

	unsigned int uiVertexSize = vVERIncomingArcs.size();

	for (unsigned int uiLoop = 0 ; uiLoop < vVERIncomingArcs.size() ; uiLoop++) {

		if (vVERIncomingArcs[uiLoop]->ARCgetVertex() == ARCParam->ARCgetVertex()) {
			vVERIncomingArcs.erase(vVERIncomingArcs.begin() + uiLoop);
			free(ARCParam);
		}
	}

	if (uiVertexSize == vVERIncomingArcs.size()) {
		throw CException(C_VERTEX_ARC_NOT_IN_VECTOR, "L'arc n'est pas present dans la liste des arcs entrants");
	}
}

/**********************************************************************
*** Delete an arc from the incoming arcs vector with uiLeaving      ***
*** E : The arc to delete										    ***
*********************************************************************/
void CVertex::VERdeleteIncomingArc(unsigned int  uiLeaving)
{
	unsigned int uiVertexSize = vVERIncomingArcs.size();
	bool deleted = false;
	unsigned int uiLoop = 0;
	while (uiLoop < uiVertexSize && deleted == false)
	{
		if (vVERIncomingArcs[uiLoop]->ARCgetVertex() == uiLeaving)
		{
			free(vVERIncomingArcs[uiLoop]);
			vVERIncomingArcs.erase(vVERIncomingArcs.begin() + uiLoop);
			deleted = true;
		}
		uiLoop++;
	}
}



// Manipulations of outcoming arcs

/************************************************
*** Get the size of the outcoming arcs vector ***
*** R : the size of the vector                ***
************************************************/
unsigned int CVertex :: VERgetOutcomingVectorSize() const {
	return vVEROutcomingArcs.size();
}

/*******************************************************************************
*** Get the arc's destination value from the incoming vector at the position ***
*** E : uiIndex the position                                                 ***
*******************************************************************************/
unsigned int CVertex::VERgetOutcomingArcDestination(unsigned int uiIndex) const {
	return vVEROutcomingArcs[uiIndex]->ARCgetVertex();
}

/********************************************
*** Add an arc to the outcoming arcs list ***
*** E : ARCParam the arc to add           ***
********************************************/
void CVertex::VERaddOutcomingArc(CArc *ARCParam) {

	if (ARCParam->ARCgetVertex() == uiVERNumber) {
		throw CException(C_VERTEX_ITSELF, "Un sommet ne peut pas pointer vers lui-meme");
	}

	unsigned int uiOutcomingVectorSize = vVEROutcomingArcs.size();

	for (unsigned int uiLoop = 0 ; uiLoop < uiOutcomingVectorSize; uiLoop++) {
		if (vVEROutcomingArcs[uiLoop]->ARCgetVertex() == ARCParam->ARCgetVertex()) {
			throw CException(C_VERTEX_ARC_ALREADY_EXISTS, "L'arc existe deja dans la liste des arcs sortants");
		}
	}

	vVEROutcomingArcs.push_back(ARCParam);
}

/***************************************************
*** Delete an arc from the outcoming arcs vector ***
*** E : The arc to delete                        ***
***************************************************/
void CVertex::VERdeleteOutcomingArc(CArc *ARCParam) {

	unsigned int uiVertexSize = vVEROutcomingArcs.size();

	for (unsigned int uiLoop = 0 ; uiLoop < vVEROutcomingArcs.size() ; uiLoop++) {

		if (vVEROutcomingArcs[uiLoop]->ARCgetVertex() == ARCParam->ARCgetVertex()) {
			vVEROutcomingArcs.erase(vVEROutcomingArcs.begin() + uiLoop);
			free(ARCParam);
		}
	}

	if (uiVertexSize == vVEROutcomingArcs.size()) {
		throw CException(C_VERTEX_ARC_NOT_IN_VECTOR, "L'arc n'est pas present dans la liste des arcs entrants");
	}
}

/***************************************************
*** Delete an arc from the outcoming arcs vector ***
*** E : The arc to delete with uIDestination     ***
***************************************************/
void CVertex::VERdeleteOutcomingArc(unsigned int  uiDestination)
{
	unsigned int uiVertexSize = vVEROutcomingArcs.size();
	bool deleted = false;
	unsigned int uiLoop = 0;
	while (uiLoop < uiVertexSize && deleted == false)
	{
		if (vVEROutcomingArcs[uiLoop]->ARCgetVertex() == uiDestination)
		{
			free(vVEROutcomingArcs[uiLoop]);
			vVEROutcomingArcs.erase(vVEROutcomingArcs.begin() + uiLoop);
			deleted = true;
		}
		uiLoop++;

	}
}
/**********************************************************************
*** Return outcoming arcs											***
*********************************************************************/
void CVertex::VERswapArcs(void)
{
	vector<CArc *> temp =  vVERIncomingArcs;
	vVERIncomingArcs = vVEROutcomingArcs;
	vVEROutcomingArcs = temp;
}

// Other methods

/*******************************************************
*** Display the vertex's incoming and outcoming arcs ***
*******************************************************/
void CVertex :: VERdisplayVertex() {

	cout << "Sommet " << uiVERNumber << endl;
	cout << "Arc(s) entrant(s) : " << endl;

	if (vVERIncomingArcs.size() == 0) {
		cout << "aucun" << endl;
	} else {

		for (unsigned int uiLoop = 0 ; uiLoop < vVERIncomingArcs.size() ; uiLoop++) {
			cout << vVERIncomingArcs[uiLoop]->ARCgetVertex() << "->" << uiVERNumber << endl;
		}
	}

	cout << "Arc(s) sortant(s) : " << endl;

	if (vVEROutcomingArcs.size() == 0) {
		cout << "aucun" << endl;
	} else {
		
		for (unsigned int uiLoop = 0 ; uiLoop < vVEROutcomingArcs.size() ; uiLoop++) {
			cout << uiVERNumber << "->" << vVEROutcomingArcs[uiLoop]->ARCgetVertex() << endl;
		}

		cout << endl;
	}
}
