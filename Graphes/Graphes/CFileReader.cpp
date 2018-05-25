#include "CFileReader.h"

/***********************
*** Copy constructor ***
***********************/
CFileReader :: CFileReader(CFileReader &FIRParam) {
	uiFIRArcsNumber = FIRParam.FIRgetArcsNumber();
	uiFIRVerticesNumber = FIRParam.FIRgetVerticesNumber();

	uiFIRArcsValues = (unsigned int *) malloc (2 * uiFIRArcsNumber * sizeof(unsigned int));
	uiFIRVerticesValues = (unsigned int *)malloc(uiFIRVerticesNumber * sizeof(unsigned int));

	for (unsigned int uiLoop = 0 ; uiLoop < uiFIRArcsNumber * 2 ; uiLoop++) {
		uiFIRArcsValues[uiLoop] = FIRParam.FIRgetArcValueAt(uiLoop);
	}

	for (unsigned int uiLoop = 0 ; uiLoop < uiFIRVerticesNumber ; uiLoop++) {
		uiFIRVerticesValues[uiLoop] = FIRParam.FIRgetVertexValueAt(uiLoop);
	}
}

/********************************************************
*** Constructor creating a CFileReader with the       ***
*** path of the file we want to get informations from ***
*** E : sPath is the access to the file               ***
********************************************************/
CFileReader :: CFileReader(string sPath) {
	sFIRFilePath = sPath;
}


/***********************************
*** Destructor - Free the arrays ***
***********************************/
CFileReader :: ~CFileReader() {
	free(uiFIRArcsValues);
	free(uiFIRVerticesValues);
	uiFIRArcsValues = nullptr;
	uiFIRVerticesValues = nullptr;
}

/***************************************************************
*** This method is used to set manually the path of the file ***
*** E : sPath is the access to the file                      ***
****************************************************************/
void CFileReader :: FIRsetFilePath(string sPath) {
	sFIRFilePath = sPath;
}

/*****************************************************
*** This methods is used to get the number of arcs ***
*** R : The number of rows                         ***
*****************************************************/
unsigned int CFileReader :: FIRgetArcsNumber() {
	return uiFIRArcsNumber;
}

/***************************************************************************
*** This methods is used to get the value from the array at the position ***
*** E : uiIndex The position                                             ***
*** R : The value                                                        ***
*** Throws CException if the position is outside the array               ***
***************************************************************************/
unsigned int CFileReader :: FIRgetArcValueAt(unsigned int uiIndex) {
	
	if (uiIndex > uiFIRArcsNumber * 2) {
		throw CException(C_FILE_READER_OUT_OF_ARRAY, "Index en dehors du tableau.");
	} else {
		return uiFIRArcsValues[uiIndex];
	}
}

/*********************************************************
*** This methods is used to get the number of vertices ***
*** R : The number of rows                             ***
*********************************************************/
unsigned int CFileReader :: FIRgetVerticesNumber() {
	return uiFIRVerticesNumber;
}

/***************************************************************************
*** This methods is used to get the value from the array at the position ***
*** E : uiIndex The position                                             ***
*** R : The value                                                        ***
*** Throws CException if the position is outside the array               ***
***************************************************************************/
unsigned int CFileReader :: FIRgetVertexValueAt(unsigned int uiIndex) {

	if (uiIndex > uiFIRVerticesNumber) {
		throw CException(C_FILE_READER_OUT_OF_ARRAY, "Index en dehors du tableau.");
	} else {
		return uiFIRVerticesValues[uiIndex];
	}
}

/***************************************************
*** Return the array containing the arcs numbers ***
*** R: The array                                 ***
***************************************************/
unsigned int * CFileReader::FIRgetArcsValues() {
	return uiFIRArcsValues;
}

/********************************************************
 *** Return the array containing the vertices numbers ***
 *** R: The array                                     ***
 *******************************************************/
unsigned int * CFileReader:: FIRgetVertexValues() {
	return uiFIRVerticesValues;
}

/***************************************************
*** Fill the object with the file's informations ***
*** The file path must have been set !!          ***
***************************************************/
void CFileReader::FIRImportFromFile() {

	string sTmpToGetLines;
	string sDelimiter = "=";

	ifstream ifsFile(sFIRFilePath, ios::in);

	// Get the number of vertices
	getline(ifsFile, sTmpToGetLines);

	string sCheck = sTmpToGetLines.substr(0, 9);

	if (sCheck != "NBSommets") {
		throw CException(C_FILE_READER_INVALID_FORMAT_FROM_FILE, "La premiere ligne du fichier ne correspond pas au format impose.");
	}

	sTmpToGetLines.erase(0, sTmpToGetLines.find(sDelimiter) + 1);

	int iVerticesNumber = atoi(sTmpToGetLines.c_str());

	if (iVerticesNumber < 0) {
		throw CException(C_FILE_READER_INVALID_VERTICES_NUMBER, "Impossible d'avoir un nombre de sommets negatif.");
	}
	else {
		uiFIRVerticesNumber = iVerticesNumber;
	}

	// Get the number of arcs
	getline(ifsFile, sTmpToGetLines);

	sCheck = sTmpToGetLines.substr(0, 6);

	if (sCheck != "NBArcs") {
		throw CException(C_FILE_READER_INVALID_FORMAT_FROM_FILE, "La deuxieme ligne du fichier ne correspond pas au format impose.");
	}

	sTmpToGetLines.erase(0, sTmpToGetLines.find(sDelimiter) + 1);

	int iArcsNumber = atoi(sTmpToGetLines.c_str());

	if (iArcsNumber < 0) {
		throw CException(C_FILE_READER_INVALID_ARCS_NUMBER, "Impossible d'avoir un nombre d'arcs negatif.");
	} else {
		uiFIRArcsNumber = iArcsNumber;
	}

	// Malloc the two arrays
	uiFIRVerticesValues = (unsigned int *) malloc (uiFIRVerticesNumber * sizeof(unsigned int));
	uiFIRArcsValues = (unsigned int *) malloc (2 * uiFIRArcsNumber * sizeof(unsigned int));

	// Get the vertices values
	getline(ifsFile, sTmpToGetLines);

	if (sTmpToGetLines != "Sommets=[") {
		free(uiFIRArcsValues);
		free(uiFIRVerticesValues);
		uiFIRArcsValues = nullptr;
		uiFIRVerticesValues = nullptr;
		throw CException(C_FILE_READER_INVALID_FORMAT_FROM_FILE, "Le fichier ne correspond pas au format impose.");
	}
	
	getline(ifsFile, sTmpToGetLines);
	
	unsigned int uiVertexIndex = 0;

	while (sTmpToGetLines != "]") {

		if (uiVertexIndex == uiFIRVerticesNumber) {
			free(uiFIRArcsValues);
			free(uiFIRVerticesValues);
			uiFIRArcsValues = nullptr;
			uiFIRVerticesValues = nullptr;
			throw CException(C_FILE_READER_INCONSISTENCY_VALUES, "Incoherence entre le nombre de sommets et le nombre de valeurs.");
		}

		for (unsigned int uiLoop = 0 ; uiLoop < sTmpToGetLines.size() ; uiLoop++) {
			if (!isdigit(sTmpToGetLines[uiLoop])) {
				free(uiFIRArcsValues);
				free(uiFIRVerticesValues);
				uiFIRArcsValues = nullptr;
				uiFIRVerticesValues = nullptr;
				throw CException(C_FILE_READER_INVALID_VERTICES_VALUE, "Valeur de sommet incorrecte.");
			}
		}

		uiFIRVerticesValues[uiVertexIndex] = atoi(sTmpToGetLines.c_str());
		uiVertexIndex++;
		getline(ifsFile, sTmpToGetLines);
	}

	if (uiVertexIndex < uiFIRVerticesNumber) {
		free(uiFIRArcsValues);
		free(uiFIRVerticesValues);
		uiFIRArcsValues = nullptr;
		uiFIRVerticesValues = nullptr;
		throw CException(C_FILE_READER_INCONSISTENCY_VALUES, "Incoherence entre le nombre de sommets et le nombre de valeurs.");
	}

	// Check if we have the same value twice in the array
	for (unsigned int uiLoop1 = 0 ; uiLoop1 < uiFIRVerticesNumber ; uiLoop1++) {
		for (unsigned int uiLoop2 = uiLoop1 + 1 ; uiLoop2 < uiFIRVerticesNumber ; uiLoop2++) {
			if (uiFIRVerticesValues[uiLoop1] == uiFIRVerticesValues[uiLoop2]) {
				free(uiFIRArcsValues);
				free(uiFIRVerticesValues);
				uiFIRArcsValues = nullptr;
				uiFIRVerticesValues = nullptr;
				throw CException(C_FILE_READER_SAME_VALUE, "Deux sommets ont le meme identifiant.");
			}
		}
	}

	// Get the arcs values
	getline(ifsFile, sTmpToGetLines);

	if (sTmpToGetLines != "Arcs=[") {
		free(uiFIRArcsValues);
		free(uiFIRVerticesValues);
		uiFIRArcsValues = nullptr;
		uiFIRVerticesValues = nullptr;
		throw CException(C_FILE_READER_INVALID_FORMAT_FROM_FILE, "Le fichier ne correspond pas au format impose.");
	}

	getline(ifsFile, sTmpToGetLines);

	unsigned int uiArcIndex = 0;

	while (sTmpToGetLines != "]") {
		
		if (uiArcIndex == uiFIRArcsNumber * 2) {
			free(uiFIRArcsValues);
			free(uiFIRVerticesValues);
			uiFIRArcsValues = nullptr;
			uiFIRVerticesValues = nullptr;
			throw CException(C_FILE_READER_INCONSISTENCY_VALUES, "Incoherence entre le nombre de sommets et le nombre de valeurs.");
		}

		string sValue = "";

		for (unsigned int uiLoop = 0 ; uiLoop < sTmpToGetLines.length() + 1 ; uiLoop++) {

			if (sTmpToGetLines[uiLoop] != ' ' && sTmpToGetLines[uiLoop] != '\0') {
				if (!isdigit(sTmpToGetLines[uiLoop])) {
					free(uiFIRArcsValues);
					free(uiFIRVerticesValues);
					uiFIRArcsValues = nullptr;
					uiFIRVerticesValues = nullptr;
					throw CException(C_FILE_READER_INVALID_ARCS_VALUE, "Valeur d'arc incorrecte.");
				} else {
					sValue += sTmpToGetLines[uiLoop];
				}
			} else {
				uiFIRArcsValues[uiArcIndex] = atoi(sValue.c_str());
				uiArcIndex++;
				sValue = "";
			}
		}

		getline(ifsFile, sTmpToGetLines);
	}
	
	if (uiArcIndex < uiFIRArcsNumber * 2) {
		free(uiFIRArcsValues);
		free(uiFIRVerticesValues);
		uiFIRArcsValues = nullptr;
		uiFIRVerticesValues = nullptr;
		throw CException(C_FILE_READER_INCONSISTENCY_VALUES, "Incoherence entre le nombre de sommets et le nombre de valeurs.");
	}
}