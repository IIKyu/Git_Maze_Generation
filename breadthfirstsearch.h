#ifndef BREADTHFIRSTSEARCH_H
#define BREADTHFIRSTSEARCH_H

#include <vector>
#include <memory>
#include <random>

#include "cellborder.h"

typedef std::vector<std::vector<std::pair<int, std::shared_ptr<CellBorder>>> >Graph;

class BreadthFirstSearch {
public:
	BreadthFirstSearch();
	std::vector<std::pair<int, int>> MinimumSpanningTree(int, const Graph&);

private:
	std::vector<bool> visited;
	std::vector<int> currentlevel, nextlevel;

	/** Proper to breadthfirstsearch **/
	std::vector<std::pair<int, int>> minimumspanningtree;
	std::random_device randomdevice;
	std::mt19937 generator;
	/** ****************************** */
};

#endif /* end of include guard: BREADTHFIRSTSEARCH_H */
