#include "CArc.h"
#include "CException.h"
#include "CFileReader.h"
#include "CGraph.h"
#include "CVertex.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {
	
	/*vector<CGraph> GRAGraphs;
	
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
	}*/

	CFileReader FIRfileReader("C:\\Users\\Boop\\Desktop\\graphe.txt");

	try {
		FIRfileReader.FIRImportFromFile();
	}
	catch (CException EXCError) {
		EXCError.EXCDisplay();
	}
	
	CGraph graph(FIRfileReader);

	graph.GRAdisplayGraph();

	cout << "============================" << endl;

	vector<int> viParam;
	graph.GRAenuStableMax(viParam);

	getchar();

	return 0;
}