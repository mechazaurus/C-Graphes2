#ifndef C_GRAPH
#define C_GRAPH 0

#include "CVertex.h"
#include "CFileReader.h"
#include <vector>

#define C_GRAPH_VERTEX_ALREADY_EXISTS 1600
#define C_GRAPH_VERTEX_NOT_IN_VECTOR 1601

using namespace std;

class CGraph {

private :

	// Attributes
	vector<CVertex*> vGRAVertices;

public :

	/**************************
	*** Default constructor ***
	*** Does nothing        ***
	**************************/
	CGraph() {}

	/***********************
	*** Copy constructor ***
	***********************/
	CGraph(const CGraph &GRAParam);

	/***************************************************************
	*** Constructors taking a CFileReader                        ***
	*** It will construct the graph with the file's informations ***
	*** E : the file to use                                      ***
	***************************************************************/
	CGraph(CFileReader FIRParam);

	/****************************************************
	*** Destructor - Free the vertices (and the arcs) ***
	****************************************************/
	~CGraph();



	// Manipulations of vertices vector

	/******************************************
	*** Get the size of the vertices vector ***
	*** R : the size of the vector          ***
	******************************************/
	unsigned int GRAgetVerticesVectorSize() const;

	/****************************************
	*** Add a vertex to the vertices list ***
	*** E : VERParam the vertex to add    ***
	****************************************/
	void GRAaddVertex(CVertex *VERParam);

	/*******************************************
	*** Delete a vertex from vertices vector ***
	*** E : The arc to delete                ***
	*******************************************/
	void GRAdeleteVertex(CVertex *VERParam);

	/*******************************************
	*** Get vector of Vextex                 ***
	*** R : The vector of Vertex             ***
	*******************************************/
	vector<CVertex*> GRAgetVerticesVector();

	/*******************************************
	*** Get the vertex at the index position ***
	*** R : The vertex                       ***
	*******************************************/
	CVertex* GRAgetVertexAtIndex(unsigned int uiParam) const;
	
	/*******************************************
	*** Delete completely a Vertex           ***
	***  E : The vertex to delete            ***
	*******************************************/
	void GRAFullyDeleteVertex(CVertex *VERParam);

	/**********************************************
	*** Get Vertex with uiNumber number         ***
	***  E : The vertex with uiNumber to return ***
	**********************************************/
	CVertex* GRAgetVertex(unsigned int uiNumber);

	/*******************************************
	*** Get Vertex index				    ***
	***  E : The vertex					    ***
	*******************************************/
	unsigned int GRAgetVertex(CVertex *VERParam);

	/*******************************************
	*** Reverse all arcs 				    ***
	***									    ***
	*******************************************/
	void GRAreverseGraph(void);


	// Other methods

	/************************
	*** Display the graph ***
	************************/
	void GRAdisplayGraph();
};

#endif