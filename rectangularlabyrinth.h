#ifndef RECTANGULARLABYRINTH_H
#define RECTANGULARLABYRINTH_H

#include "labyrinth.h"

class RectangularLabyrinth: public Labyrinth {
public:

	/** Proper to rectangular maze **/
	RectangularLabyrinth(int, int);
	/** ************************** **/

	virtual void InitialiseGraph();

private:

	virtual std::tuple<double, double, double, double> GetCoordinateBounds() const;

	/** Proper to rectangular maze **/
	int width_, height_;
	int VertexIndex(int, int);
	/** ************************** **/
};

#endif /* end of include guard: RECTANGULARLABYRINTH_H */
