#ifndef RECTANGULARMaze_H
#define RECTANGULARMaze_H

#include "maze.h"

class RectangularMaze: public Maze {
public:

	/** Proper to rectangular maze **/
	RectangularMaze(int, int);
	/** ************************** **/

	virtual void InitialiseGraph();

private:

	virtual std::tuple<double, double, double, double> GetCoordinateBounds() const;

	/** Proper to rectangular maze **/
	int width_, height_;
	int VertexIndex(int, int);
	/** ************************** **/
};

#endif /* end of include guard: RECTANGULARMaze_H */
