#include <cstring>
#include <iostream>
#include <map>
#include <string>

#include "depthfirstsearch.h"
#include "breadthfirstsearch.h"
#include "rectangularmaze.h"
#include "circularmaze.h"

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

	Maze *maze;
	MinimumSpanningtreeAlgorithm *algorithm;

	switch (optionmap["-m"]) {
	case 0: {
		if (optionmap["-w"] < 1 or optionmap["-h"] < 1) {
			std::cerr << "Invalide size " << optionmap["-w"] << "x"
					<< optionmap["-h"] << " for rectangular Maze\n";
			return 1;
		}

		std::cout << "Rectangular Maze of size " << optionmap["-w"] << "x"
				<< optionmap["-h"] << "\n";
		maze = new RectangularMaze(optionmap["-w"], optionmap["-h"]);

		break;
	}

	case 1: {
		if (optionmap["-s"] < 1) {
			std::cerr << "Invalide size " << optionmap["-s"]
					<< " for circular Maze\n";
			return 1;
		}
		std::cout << "Circular Maze of size " << optionmap["-s"] << "\n";
		maze = new CircularMaze(optionmap["-s"]);

		break;
	}

	default:
		std::cerr << "Unknown Maze type " << optionmap["-m"];

		return 1;
	}

	switch (optionmap["-a"]) {

	case 0: {
		std::cout << "Maze generation using Depth-first search\n";
		algorithm = new DepthFirstSearch();

		break;
	}

	case 1: {
		std::cout << "Maze generation using Breadth-first search\n";
		algorithm = new BreadthFirstSearch();

		break;
	}

	default:
		std::cerr << "Unknown algorithm type " << optionmap["-a"];
		return 1;
	}

	std::cout << "Initialising graph..." << std::endl;
	maze->InitialiseGraph();

	std::cout << "Generating Maze..." << std::endl;
	maze->GenerateMaze(algorithm);

	if (optionmap["-t"] == 0) {
		std::cout << "Rendering maze to '" << outputprefix << ".svg'..."
				<< std::endl;
		maze->PrintMazeSVG(outputprefix);
	} else {
		std::cout << "Exporting maze plotting parameters to '" << outputprefix
				<< ".plt' ..." << std::endl;
		maze->PrintMazePNG(outputprefix);
		std::cout << "Rendering maze to '" << outputprefix
				<< ".png' using gnuplot..." << std::endl;
		system(("gnuplot '" + outputprefix + ".plt'").c_str());
	}
	return 0;
}
