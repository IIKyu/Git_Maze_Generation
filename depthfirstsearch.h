#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "minimumspanningtreealgorithm.h"

class DepthFirstSearch: public MinimumSpanningtreeAlgorithm {
public:
	std::vector<std::pair<int, int>> MinimumSpanningTree(int, const Graph&);

private:
	/** Proper to depthfirstsearch **/
	std::vector<bool> visited;
	void DFS(int, const Graph &);
	/** ******************************* **/
};

#endif /* end of include guard: DEPTHFIRSTSEARCH */
