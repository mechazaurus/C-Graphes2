#include "CArc.h"
#include "CException.h"
#include "CFileReader.h"
#include "CGraph.h"
#include "CVertex.h"
#include <cstdio>
#include <iostream>

using namespace std;

int main(int argc, char * argv[]) {

	for (int iLoop = 1; iLoop < argc; iLoop++) {

		CFileReader FIRfileReader(argv[iLoop]);

		try {
			FIRfileReader.FIRImportFromFile();
		}
		catch (CException EXCError) {
			EXCError.EXCDisplay();
		}

		CGraph graph(FIRfileReader);

		graph.GRAdisplayGraph();
		graph.GRAenuStableMax();

	}

	return 0;
}