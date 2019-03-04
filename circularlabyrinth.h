#ifndef CIRCULARLABYRINTH_H
#define CIRCULARLABYRINTH_H

#include <memory>
#include <vector>
#include "cellborder.h"
#include "depthfirstsearch.h"

class CircularLabyrinth {
public:

	/** Proper to circular maze **/
	CircularLabyrinth(int);
	/** *********************** **/
	void GenerateLabyrinth(DepthFirstSearch*);
	void PrintLabyrinthSVG(const std::string&);
	void RemoveBorders(const std::vector<std::pair<int, int>>&);
	void InitialiseGraph();

private:
	// Solving a maze is equivalent to finding a path in a graph
	int vertices_;
	std::vector<std::vector<std::pair<int, std::shared_ptr<CellBorder>>> >adjacencylist_;
	int startvertex_, endvertex_;
	std::tuple<double, double, double, double> GetCoordinateBounds();

	/** Proper to circular maze **/
	int size_;
	std::vector<int> ringnodecount_, ringnodeprefixsum_;
	/** *********************** **/

};

#endif /* end of include guard: CIRCULARLABYRINTH_H */
