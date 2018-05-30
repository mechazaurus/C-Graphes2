#include "CArc.h"
#include "CException.h"
#include "CGraph.h"
#include "CVertex.h"
#include <algorithm>

/***********************
*** Copy constructor ***
***********************/
CGraph :: CGraph(const CGraph &GRAParam) {
	
	const unsigned int uiVectorSize = GRAParam.GRAgetVerticesVectorSize();

	for (unsigned int uiLoop = 0 ; uiLoop < uiVectorSize ; uiLoop++) {
		vGRAVertices.push_back(new CVertex(*GRAParam.GRAgetVertexAtIndex(uiLoop)));
	}
}

/**************************************************************
*** Constructors taking a CFileReader                       ***
*** It will construct the graph wit the file's informations ***
*** E : the file to use                                     ***
**************************************************************/
CGraph :: CGraph(CFileReader FIRParam) {

	if (FIRParam.FIRgetArcsValues() == nullptr || FIRParam.FIRgetVertexValues() == nullptr) {

	} else {
		for (unsigned int uiLoop = 0 ; uiLoop < FIRParam.FIRgetVerticesNumber() ; uiLoop++) {
			vGRAVertices.push_back(new CVertex(FIRParam.FIRgetVertexValueAt(uiLoop)));
		}

		for (unsigned int uiLoop1 = 0 ; uiLoop1 < FIRParam.FIRgetArcsNumber() * 2 ; uiLoop1+=2) {

			for (unsigned int uiLoop2 = 0; uiLoop2 < FIRParam.FIRgetVerticesNumber(); uiLoop2++) {
				if (FIRParam.FIRgetArcValueAt(uiLoop1) == vGRAVertices[uiLoop2]->VERgetVertexNumber()) {
					vGRAVertices[uiLoop2]->VERaddOutcomingArc(new CArc(FIRParam.FIRgetArcValueAt(uiLoop1 + 1)));
				}
			}

			for (unsigned int uiLoop3 = 0; uiLoop3 < FIRParam.FIRgetVerticesNumber(); uiLoop3++) {
				if (FIRParam.FIRgetArcValueAt(uiLoop1 + 1) == vGRAVertices[uiLoop3]->VERgetVertexNumber()) {
					vGRAVertices[uiLoop3]->VERaddIncomingArc(new CArc(FIRParam.FIRgetArcValueAt(uiLoop1)));
				}
			}
		}
	}
}

/****************************************************
*** Destructor - Free the vertices (and the arcs) ***
****************************************************/
CGraph :: ~CGraph() {

	unsigned int uiVectorSize = vGRAVertices.size();

	unsigned int uiCounter = 0;
	unsigned int zero = 0;
	while (uiCounter < uiVectorSize)
	{
		GRAFullyDeleteVertex(vGRAVertices[0]);
		uiCounter++;
	}

	vGRAVertices.clear();
}



// Manipulations of vertices vector

/******************************************
*** Get the size of the vertices vector ***
*** R : the size of the vector          ***
******************************************/
unsigned int CGraph :: GRAgetVerticesVectorSize() const {
	return vGRAVertices.size();
}

/****************************************
*** Add a vertex to the vertices list ***
*** E : VERParam the vertex to add    ***
****************************************/
void CGraph :: GRAaddVertex(CVertex *VERParam) {

	unsigned int uiVectorSize = vGRAVertices.size();

	for (unsigned int uiLoop = 0 ; uiLoop < uiVectorSize ; uiLoop++) {
		if (VERParam->VERgetVertexNumber() == vGRAVertices[uiLoop]->VERgetVertexNumber()) {
			throw CException(C_GRAPH_VERTEX_ALREADY_EXISTS, "Le sommet existe deja dans le graphe.");
		}
	}

	vGRAVertices.push_back(VERParam);
}

/*******************************************
*** Delete a vertex from vertices vector ***
*** E : The vertex to delete             ***
*******************************************/
void CGraph :: GRAdeleteVertex(CVertex *VERParam) {

	unsigned int uiVectorSize = vGRAVertices.size();

	for (unsigned int uiLoop = 0 ; uiLoop < vGRAVertices.size() ; uiLoop++) {
		if (VERParam->VERgetVertexNumber() == vGRAVertices[uiLoop]->VERgetVertexNumber()) {
			vGRAVertices.erase(vGRAVertices.begin() + uiLoop);
			delete(VERParam);
		}
	}

	if (uiVectorSize == vGRAVertices.size()) {
		throw CException(C_GRAPH_VERTEX_NOT_IN_VECTOR, "Le sommet n'est pas present dans le graphe.");
	}
}

/*******************************************
*** Get vector of Vextex                 ***
*** R : The vector of Vertex             ***
*******************************************/
vector<CVertex*> CGraph :: GRAgetVerticesVector() {
	return vGRAVertices;
}

/*******************************************
*** Get the vertex at the index position ***
*** R : The vertex                       ***
*******************************************/
CVertex* CGraph :: GRAgetVertexAtIndex(unsigned int uiParam) const {
	return vGRAVertices[uiParam];
}

/*******************************************
*** Delete completely a Vertex           ***
***  E : The vertex to delete            ***
*******************************************/
void CGraph::GRAFullyDeleteVertex(CVertex *VERParam)
{
	for (unsigned int uiLoop = 0; uiLoop < VERParam->VERgetIncomingVectorSize(); uiLoop++)
	{
		unsigned int uiVertexPointing = VERParam->VERgetIncomingArcDestination(uiLoop);
		GRAgetVertex(uiVertexPointing)->VERdeleteOutcomingArc(VERParam->VERgetVertexNumber());
	}

	for (unsigned int uiLoop = 0; uiLoop < VERParam->VERgetOutcomingVectorSize(); uiLoop++)
	{
		unsigned int uiVertexPointing = VERParam->VERgetOutcomingArcDestination(uiLoop);
		GRAgetVertex(uiVertexPointing)->VERdeleteIncomingArc(VERParam->VERgetVertexNumber());
	}
	unsigned int uiPosition = GRAgetVertex(VERParam);
	delete(VERParam);
	vGRAVertices.erase(vGRAVertices.begin() + uiPosition);
}

/**********************************************
*** Get vextex with uiNumber                ***
***  E : The vertex with uiNumber to return ***
**********************************************/
CVertex* CGraph::GRAgetVertex(unsigned int uiNumber)
{
	for (unsigned int uiLoop = 0; uiLoop < vGRAVertices.size(); uiLoop++)
	{
		if (vGRAVertices[uiLoop]->VERgetVertexNumber() == uiNumber)
		{
			return vGRAVertices[uiLoop];
		}
	}
	throw CException(C_GRAPH_VERTEX_NOT_IN_VECTOR, "Le sommet avec le nombre uiNumber n'est pas present dans le graphe.");
}

/*******************************************
*** Get Vertex index				    ***
***  E : The vertex					    ***
*******************************************/
unsigned int CGraph::GRAgetVertex(CVertex *VERParam)
{
	for (unsigned int uiLoop = 0; uiLoop < vGRAVertices.size(); uiLoop++)
	{
		if (vGRAVertices[uiLoop]->VERgetVertexNumber() == VERParam->VERgetVertexNumber())
		{
			return uiLoop;
		}
	}
	throw CException(C_GRAPH_VERTEX_NOT_IN_VECTOR, "Le sommet n'est pas present dans le graphe.");

}

/*******************************************
*** Reverse all arcs 				    ***
***									    ***
*******************************************/
void CGraph::GRAreverseGraph(void)
{
	for (unsigned int uiLoop = 0; uiLoop < vGRAVertices.size(); uiLoop++)
	{
		vGRAVertices[uiLoop]->VERswapArcs();
	}
}




// Other methods

/************************
*** Display the graph ***
************************/
void CGraph :: GRAdisplayGraph() {

	cout << "Composition du graphe :" << endl;
	cout << endl;

	unsigned int uiVectorSize = vGRAVertices.size();

	for (unsigned int uiLoop = 0 ; uiLoop < uiVectorSize ; uiLoop++) {
		vGRAVertices[uiLoop]->VERdisplayVertex();
	}
}


/***********************************************
*** Compute the maximum independant vertices ***
*** R : the vector of vertices' value        ***
***********************************************/
void CGraph :: GRAenuStableMax(vector<int> viParam) {

	//sort(vGRAVertices.begin(), vGRAVertices.end());

	if (viParam.empty()) {
		viGRAStableMax.clear();
	}

	if (vGRAVertices.empty()) {
		if (viParam.size() >= viGRAStableMax.size()) {
			viGRAStableMax = viParam;
		}
	} else {
		for (unsigned int uiLoop1 = 0 ; uiLoop1 < vGRAVertices.size() ; uiLoop1++) {

			vector<CVertex*> vVERTemp;
			vVERTemp.push_back(new CVertex(*vGRAVertices[uiLoop1]));

			unsigned int uiVertexNumber = vGRAVertices[uiLoop1]->VERgetVertexNumber();
			GRAFullyDeleteVertex(vGRAVertices[uiLoop1]);

			viParam.push_back(uiVertexNumber);

			GRAdisplayGraph();
			cout << "viParam[0]" << viParam[0] << endl;
			/*
			unsigned int uiSize = GRAgetVertexAtIndex(uiLoop1)->VERgetIncomingVectorSize();

			// récupérer la taille avant
			for (unsigned int uiLoop2 = 0 ; uiLoop2 < uiSize ; uiLoop2++) {
				unsigned int uiVertexNumber = GRAgetVertexAtIndex(uiLoop1)->VERgetIncomingArcDestination(uiLoop2);
				vVERTemp.push_back(new CVertex(*GRAgetVertex(uiVertexNumber)));
				
				for (unsigned int uiLoop3 = 0 ; uiLoop3 < vGRAVertices.size() ; uiLoop3++) {

					if (GRAgetVertexAtIndex(uiLoop3)->VERgetVertexNumber() == GRAgetVertexAtIndex(uiLoop1)->VERgetIncomingArcDestination(uiLoop2)) {
						GRAFullyDeleteVertex(vGRAVertices[uiLoop3]);
					}
				}
			}

			GRAenuStableMax(viParam);

			for (unsigned int uiLoop = 0; uiLoop < vVERTemp.size(); uiLoop++) {
				GRAaddVertex(vVERTemp[uiLoop]);
			}

			vVERTemp.clear();

			sort(vGRAVertices.begin(), vGRAVertices.end());*/
		}
	}
}