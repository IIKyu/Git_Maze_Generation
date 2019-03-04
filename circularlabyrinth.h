#ifndef CIRCULARLABYRINTH_H
#define CIRCULARLABYRINTH_H

#include "labyrinth.h"

class CircularLabyrinth: public Labyrinth {
public:

	/** Proper to circular maze **/
	CircularLabyrinth(int);
	/** *********************** **/
	void InitialiseGraph();

private:
	virtual std::tuple<double, double, double, double> GetCoordinateBounds() const;

	/** Proper to circular maze **/
	int size_;
	std::vector<int> ringnodecount_, ringnodeprefixsum_;
	/** *********************** **/

};

#endif /* end of include guard: CIRCULARLABYRINTH_H */
