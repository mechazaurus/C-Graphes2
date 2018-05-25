#include "CArc.h"
#include "CException.h"
#include "CFileReader.h"
#include "CGraph.h"
#include "CVertex.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	
	vector<CGraph> GRAGraphs;
	
	for (int iLoop = 1 ; iLoop < argc ; iLoop++) {

		CFileReader FIRfileReader(argv[iLoop]);

		try {
			FIRfileReader.FIRImportFromFile();
		} catch (CException EXCError) {
			EXCError.EXCDisplay();
		}

		GRAGraphs.push_back(CGraph(FIRfileReader));
	}

	for (int iLoop = 0 ; iLoop < argc - 1 ; iLoop++) {
		cout << endl << "Graphe " << iLoop + 1 << endl;
		GRAGraphs[iLoop].GRAdisplayGraph();
		cout << "Inversion des arcs..." << endl << endl;
		GRAGraphs[iLoop].GRAreverseGraph();
		GRAGraphs[iLoop].GRAdisplayGraph();
		cout << "==================================" << endl;
	}

	return 0;
}