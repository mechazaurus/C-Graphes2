#ifndef C_VERTEX
#define C_VERTEX 0

#include "CArc.h"
#include <iostream>
#include <vector>

#define C_VERTEX_ARC_ALREADY_EXISTS 1500
#define C_VERTEX_ARC_NOT_IN_VECTOR 1501
#define C_VERTEX_ITSELF 1502

using namespace std;

class CVertex {

private :

	// Attributes
	unsigned int uiVERNumber;
	vector<CArc *> vVERIncomingArcs;
	vector<CArc *> vVEROutcomingArcs;

	/***************************************
	*** Default constructor              ***
	*** Set the value of the vertex at 0 ***
	*** Can't be used by users           ***
	***************************************/
	CVertex();

public :

	/***********************
	*** Copy constructor ***
	***********************/
	CVertex(const CVertex &VERParam);

	/**********************************************
	*** Constructor setting the vertex's number ***
	*** E : uiParam the value                   ***
	**********************************************/
	CVertex(unsigned int uiParam);

	/*********************************
	*** Destructor - Free the arcs ***
	*********************************/
	~CVertex();

	/******************************
	*** Get the vertex's number ***
	*** R: the vertex's number  ***
	******************************/
	unsigned int VERgetVertexNumber() const;



	// Manipulations of incoming arcs

	/************************************************
	 *** Get the size of the incoming arcs vector ***
	 *** R : the size of the vector               ***
	 ***********************************************/
	unsigned int VERgetIncomingVectorSize() const;

	/***********************************************************************
	*** Get the arc's destination value from the vector at the position ***
	*** E : uiIndex the position                                        ***
	**********************************************************************/
	unsigned int VERgetIncomingArcDestination(unsigned int uiIndex) const;

	/**********************************************
	 *** Add an arc to the incoming arcs vector ***
	 *** E : ARCParam the arc to add            ***
	 *********************************************/
	void VERaddIncomingArc(CArc *ARCParam);

	/***************************************************
	 *** Delete an arc from the incoming arcs vector ***
	 *** E : The arc to delete                       ***
	 **************************************************/
	void VERdeleteIncomingArc(CArc *ARCParam);

	/**********************************************************************
	*** Delete an arc from the incoming arcs vector with uiLeaving      ***
	*** E : The arc to delete										    ***
	*********************************************************************/
	void VERdeleteIncomingArc(unsigned int uiLeaving);



	// Manipulations of outcoming arcs

	/************************************************
	*** Get the size of the outcoming arcs vector ***
	*** R : the size of the vector                ***
	************************************************/
	unsigned int VERgetOutcomingVectorSize() const;

	/*******************************************************************************
	*** Get the arc's destination value from the incoming vector at the position ***
	*** E : uiIndex the position                                                 ***
	*******************************************************************************/
	unsigned int VERgetOutcomingArcDestination(unsigned int uiIndex) const;

	/**********************************************
	*** Add an arc to the outcoming arcs vector ***
	*** E : ARCParam the arc to add             ***
	**********************************************/
	void VERaddOutcomingArc(CArc *ARCParam);

	/***************************************************
	*** Delete an arc from the outcoming arcs vector ***
	*** E : The arc to delete                        ***
	***************************************************/
	void VERdeleteOutcomingArc(CArc *ARCParam);

	/**********************************************************************
	*** Delete an arc from the outcoming arcs vector with uiDestination ***
	*** E : The arc to delete										    ***
	*********************************************************************/
	void VERdeleteOutcomingArc(unsigned int  uiDestination);


	/**********************************************************************
	*** Return outcoming arcs											***
	*********************************************************************/
	void VERswapArcs(void);


	// Other methods

	/********************************************************
	 *** Display the vertex's incoming and outcoming arcs ***
	 *******************************************************/
	void VERdisplayVertex();
};

#endif