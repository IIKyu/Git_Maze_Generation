#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include "depthfirstsearch.h"
#include "breadthfirstsearch.h"
#include "rectangularlabyrinth.h"

int main(int argc, char *argv[]) {

	std::string outputprefix = "maze";
	std::map<std::string, int> optionmap { { "-w", 20 }, { "-h", 20 }, { "-a", 0 } };

	/* parsing command line parameters */

	 for (int i = 1; i < argc; i++) {
	    if (optionmap.find(argv[i]) == optionmap.end()) {
	      std::cerr << "Unknown argument " << argv[i] << "\n";
	      return 1;
	    }

	    if (i + 1 == argc) {
	      std::cerr << "Missing option for argument " << argv[i] << std::endl;
	      return 1;
	    }
	    int x;
	    try {
	      x = std::stoi(argv[i + 1]);
	    } catch (...) {
	      std::cerr << "Invalid argument " << argv[i + 1] << " for option "
	                << argv[i] << "\n";
	      return 1;
	    }
	    optionmap[argv[i++]] = x;
	  }


	RectangularLabyrinth *rectangularLabyrinth;
	MinimumSpanningtreeAlgorithm *algorithm;

	if (optionmap["-w"] < 1 or optionmap["-h"] < 1) {
		std::cerr << "Invalide size " << optionmap["-w"] << "x"
				<< optionmap["-h"] << " for rectangular labyrinth\n";
		return 1;
	}

	std::cout << "Rectangular labyrinth of size " << optionmap["-w"] << "x"
			<< optionmap["-h"] << "\n";
	rectangularLabyrinth = new RectangularLabyrinth(optionmap["-w"], optionmap["-h"]);


	switch (optionmap["-a"]) {

	case 0: {
		std::cout << "Labyrinth generation using Depth-first search\n";
		algorithm = new DepthFirstSearch();

		break;
	}

	case 1: {
		std::cout << "Labyrinth generation using Breadth-first search\n";
		algorithm = new BreadthFirstSearch();

		break;
	}

	default:
		std::cerr << "Unknown algorithm type " << optionmap["-a"];
		return 1;
	}

	std::cout << "Initialising graph..." << std::endl;
	rectangularLabyrinth->InitialiseGraph();

	std::cout << "Generating labyrinth..." << std::endl;
	rectangularLabyrinth->GenerateLabyrinth(algorithm);

	rectangularLabyrinth->PrintLabyrinthSVG(outputprefix);

	return 0;
}

