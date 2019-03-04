#ifndef CIRCULARMAZE_H
#define CIRCULARMAZE_H

#include "maze.h"

class CircularMaze: public Maze {
public:

	/** Proper to circular maze **/
	CircularMaze(int);
	/** *********************** **/
	void InitialiseGraph();

private:
	virtual std::tuple<double, double, double, double> GetCoordinateBounds() const;

	/** Proper to circular maze **/
	int size_;
	std::vector<int> ringnodecount_, ringnodeprefixsum_;
	/** *********************** **/

};

#endif /* end of include guard: CIRCULARMAZE_H */
