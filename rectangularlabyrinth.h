#ifndef RECTANGULARLABYRINTH_H
#define RECTANGULARLABYRINTH_H

#include <memory>
#include <vector>
#include "cellborder.h"
#include "depthfirstsearch.h"
#include "breadthfirstsearch.h"

class RectangularLabyrinth {
public:

	/** Proper to rectangular maze **/
	RectangularLabyrinth(int, int);
	/** ************************** **/
	void GenerateLabyrinth(MinimumSpanningtreeAlgorithm*);
	void PrintLabyrinthSVG(const std::string&);
	void RemoveBorders(const std::vector<std::pair<int, int>>&);
	void InitialiseGraph();

private:
	// Solving a maze is equivalent to finding a path in a graph
	int vertices_;
	std::vector<std::vector<std::pair<int, std::shared_ptr<CellBorder>>> >adjacencylist_;
	int startvertex_, endvertex_;

	std::tuple<double, double, double, double> GetCoordinateBounds();

	/** Proper to rectangular maze **/
	int width_, height_;
	int VertexIndex(int, int);
	/** ************************** **/
};

#endif /* end of include guard: RECTANGULARLABYRINTH_H */
