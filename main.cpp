#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include "depthfirstsearch.h"
#include "breadthfirstsearch.h"
#include "rectangularlabyrinth.h"
#include "circularlabyrinth.h"

int main(int argc, char *argv[]) {

	std::string outputprefix = "maze";
	std::map<std::string, int> optionmap { { "-m", 0 }, { "-s", 20 },
			{ "-w", 20 }, { "-h", 20 }, { "-t", 0 }, { "-a", 0 } };

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

	Labyrinth *labyrinth;

	switch (optionmap["-m"]) {
	case 0: {
		if (optionmap["-w"] < 1 or optionmap["-h"] < 1) {
			std::cerr << "Invalide size " << optionmap["-w"] << "x"
					<< optionmap["-h"] << " for rectangular labyrinth\n";
			return 1;
		}

		std::cout << "Rectangular labyrinth of size " << optionmap["-w"] << "x"
				<< optionmap["-h"] << "\n";
		labyrinth = new RectangularLabyrinth(optionmap["-w"], optionmap["-h"]);

		break;
	}

	case 1: {
		if (optionmap["-s"] < 1) {
			std::cerr << "Invalide size " << optionmap["-s"]
					<< " for circular labyrinth\n";
			return 1;
		}
		std::cout << "Circular labyrinth of size " << optionmap["-s"] << "\n";
		labyrinth = new CircularLabyrinth(optionmap["-s"]);

		break;
	}

	default:
		std::cerr << "Unknown labyrinth type " << optionmap["-m"];

		return 1;
	}

	switch (optionmap["-a"]) {

	case 0: {
		std::cout << "Labyrinth generation using Depth-first search\n";
		DepthFirstSearch *depthFirstSearch = new DepthFirstSearch();

		std::cout << "Initialising graph..." << std::endl;
		labyrinth->InitialiseGraph();

		std::cout << "Generating labyrinth..." << std::endl;
		labyrinth->GenerateLabyrinth(depthFirstSearch);

		break;
	}

	case 1: {
		std::cout << "Labyrinth generation using Breadth-first search\n";
		BreadthFirstSearch *breadthFirstSearch = new BreadthFirstSearch();

		std::cout << "Initialising graph..." << std::endl;
		labyrinth->InitialiseGraph();

		std::cout << "Generating labyrinth..." << std::endl;
		labyrinth->GenerateLabyrinth(breadthFirstSearch);

		break;
	}

	default:
		std::cerr << "Unknown algorithm type " << optionmap["-a"];
		return 1;
	}

	if (optionmap["-t"] == 0) {
		std::cout << "Rendering maze to '" << outputprefix << ".svg'..."
				<< std::endl;
		labyrinth->PrintLabyrinthSVG(outputprefix);
	} else {
		std::cout << "Exporting maze plotting parameters to '" << outputprefix
				<< ".plt' ..." << std::endl;
		labyrinth->PrintLabyrinthPNG(outputprefix);
		std::cout << "Rendering maze to '" << outputprefix
				<< ".png' using gnuplot..." << std::endl;
		system(("gnuplot '" + outputprefix + ".plt'").c_str());
	}
	return 0;
}
