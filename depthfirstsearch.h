#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include <memory>
#include <random>

#include <vector>
#include "cellborder.h"

typedef std::vector<std::vector<std::pair<int, std::shared_ptr<CellBorder>>> >Graph;

class DepthFirstSearch {
public:
	DepthFirstSearch();
	std::vector<std::pair<int, int>> MinimumSpanningTree(int, const Graph&);

private:
	std::vector<std::pair<int, int>> minimumspanningtree;
	std::random_device randomdevice;
	std::mt19937 generator;

	/** Proper to depthfirstsearch **/
	std::vector<bool> visited;
	void DFS(int, const Graph &);
	/** ******************************* **/
};

#endif /* end of include guard: DEPTHFIRSTSEARCH */
