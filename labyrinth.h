#ifndef LABYRINTH_H
#define LABYRINTH_H

#include <memory>
#include <vector>
#include "cellborder.h"
#include "depthfirstsearch.h"

class Labyrinth {
public:
	Labyrinth(int = 0, int = 0, int = 1);
	void GenerateLabyrinth(DepthFirstSearch*);
	void PrintLabyrinthSVG(const std::string&) const;
	void PrintLabyrinthPNG(const std::string&) const;
	void RemoveBorders(const std::vector<std::pair<int, int>>&);
	virtual void InitialiseGraph() = 0;

protected:
	// Solving a maze is equivalent to finding a path in a graph
	int vertices_;
	std::vector<std::vector<std::pair<int, std::shared_ptr<CellBorder>>> >adjacencylist_;
	int startvertex_, endvertex_;

	virtual std::tuple<double, double, double, double> GetCoordinateBounds()
	const = 0;
};

#endif /* end of include guard: LABYRINTH_H */
