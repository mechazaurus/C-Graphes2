#ifndef C_FILE_READER
#define C_FILE_READER 0

#define C_FILE_READER_INVALID_FORMAT_FROM_FILE 1200
#define C_FILE_READER_INVALID_VERTICES_NUMBER 1201
#define C_FILE_READER_INVALID_ARCS_NUMBER 1202
#define C_FILE_READER_INVALID_VERTICES_VALUE 1203
#define C_FILE_READER_OUT_OF_ARRAY 1204
#define C_FILE_READER_INCONSISTENCY_VALUES 1205
#define C_FILE_READER_INVALID_ARCS_VALUE 1206
#define C_FILE_READER_SAME_VALUE 1207

#include "CException.h"
#include <fstream>
#include <iostream>
#include <string>


using namespace std;

class CFileReader {

private :

	// Attributes
	string sFIRFilePath;
	unsigned int uiFIRArcsNumber;
	unsigned int *uiFIRArcsValues;
	unsigned int uiFIRVerticesNumber;
	unsigned int *uiFIRVerticesValues;

public :

	/***********************
	*** Copy constructor ***
	***********************/
	CFileReader(CFileReader &FIRParam);

	/********************************************************
	*** Constructor creating a CFileReader with the       ***
	*** path of the file we want to get informations from ***
	*** E : sPath is the access to the file               ***
	********************************************************/
	CFileReader(string sPath);

	/***********************************
	*** Destructor - Free the arrays ***
	***********************************/
	~CFileReader();

	/***************************************************************
	*** This method is used to set manually the path of the file ***
	*** E : sPath is the access to the file                      ***
	****************************************************************/
	void FIRsetFilePath(string sPath);

	/*****************************************************
	*** This methods is used to get the number of arcs ***
	*** R : The number of rows                         ***
	*****************************************************/
	unsigned int FIRgetArcsNumber();

	/***************************************************************************
	*** This methods is used to get the value from the array at the position ***
	*** E : uiIndex The position                                             ***
	*** R : The value                                                        ***
	*** Throws CException if the position is outside the array               ***
	***************************************************************************/
	unsigned int FIRgetArcValueAt(unsigned int uiIndex);

	/*********************************************************
	*** This methods is used to get the number of vertices ***
	*** R : The number of rows                             ***
	*********************************************************/
	unsigned int FIRgetVerticesNumber();

	/***************************************************************************
	*** This methods is used to get the value from the array at the position ***
	*** E : uiIndex The position                                             ***
	*** R : The value                                                        ***
	*** Throws CException if the position is outside the array               ***
	***************************************************************************/
	unsigned int FIRgetVertexValueAt(unsigned int uiIndex);

	/***************************************************
	*** Return the array containing the arcs numbers ***
	*** R: The array                                 ***
	***************************************************/
	unsigned int * FIRgetArcsValues();

	/*******************************************************
	*** Return the array containing the vertices numbers ***
	*** R: The array                                     ***
	*******************************************************/
	unsigned int * FIRgetVertexValues();

	/***************************************************
	*** Fill the object with the file's informations ***
	*** The file path must have been set !!          ***
	***************************************************/
	void FIRImportFromFile();
};

#endif