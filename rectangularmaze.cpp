#include <algorithm>
#include <fstream>
#include <iostream>

#include "rectangularmaze.h"

RectangularMaze::RectangularMaze(int width, int height) :
		vertices_(width * height), startvertex_(0), endvertex_(
				width * height - 1), width_(width), height_(height) {
}

/** Proper to rectangular maze **/
int RectangularMaze::VertexIndex(int row, int column) {
	return row * width_ + column;
}
/** ************************** **/

void RectangularMaze::InitialiseGraph() {
	adjacencylist_.clear();
	adjacencylist_.resize(vertices_);

	/** Proper to rectangular maze **/

	// Lower and upper boundaries
	for (int i = 0; i < width_; ++i) {
		adjacencylist_[VertexIndex(0, i)].push_back(
				{ -1, std::make_shared < LineBorder > (i, 0, i + 1, 0) });
		adjacencylist_[VertexIndex(height_ - 1, i)].push_back(
				{ -1, std::make_shared < LineBorder
						> (i, height_, i + 1, height_) });
	}

	// Left and right boundaries, leaving space for entry and exit
	for (int i = 0; i < height_; ++i) {
		if (i != 0)
			adjacencylist_[VertexIndex(i, 0)].push_back(
					{ -1, std::make_shared < LineBorder > (0, i, 0, i + 1) });
		if (i != height_ - 1)
			adjacencylist_[VertexIndex(i, 0)].push_back(
					{ -1, std::make_shared < LineBorder
							> (width_, i, width_, i + 1) });
	}

	// Horizontally adjacent cells
	for (int i = 0; i < height_; ++i) {
		for (int j = 0; j < width_ - 1; ++j) {
			std::shared_ptr<LineBorder> ptr = std::make_shared < LineBorder
					> (j + 1, i, j + 1, i + 1);
			adjacencylist_[VertexIndex(i, j)].push_back(
					{ VertexIndex(i, j + 1), ptr });
			adjacencylist_[VertexIndex(i, j + 1)].push_back(
					{ VertexIndex(i, j), ptr });
		}
	}


	// Vertically adjacent cells
	for (int i = 0; i < height_ - 1; ++i) {
		for (int j = 0; j < width_; ++j) {
			std::shared_ptr<LineBorder> ptr = std::make_shared < LineBorder
					> (j, i + 1, j + 1, i + 1);
			adjacencylist_[VertexIndex(i, j)].push_back(
					{ VertexIndex(i + 1, j), ptr });
			adjacencylist_[VertexIndex(i + 1, j)].push_back(
					{ VertexIndex(i, j), ptr });
		}
	}

	/** ************************** **/
}

std::tuple<double, double, double, double> RectangularMaze::GetCoordinateBounds() {
	return std::make_tuple(0, 0, width_, height_);
}

void RectangularMaze::GenerateMaze(MinimumSpanningtreeAlgorithm* algorithm) {
	auto minimumspanningtree = algorithm->MinimumSpanningTree(vertices_,
			adjacencylist_);
	RemoveBorders(minimumspanningtree);
}


void RectangularMaze::RemoveBorders(const std::vector<std::pair<int, int>>& edges) {
	for (const auto& edge : edges) {
		int u = edge.first, v = edge.second;
		for (int i = 0; i < (int) adjacencylist_[u].size(); ++i) {
			if (adjacencylist_[u][i].first == v) {
				adjacencylist_[u].erase(adjacencylist_[u].begin() + i);
				break;
			}
		}
		for (int i = 0; i < (int) adjacencylist_[v].size(); ++i) {
			if (adjacencylist_[v][i].first == u) {
				adjacencylist_[v].erase(adjacencylist_[v].begin() + i);
				break;
			}
		}
	}
}

void RectangularMaze::PrintMazeSVG(const std::string& outputprefix) {
	std::ofstream svgfile(outputprefix + ".svg");
	if (!svgfile) {
		std::cerr << "Error opening " << outputprefix << ".svg for writing.\n";
		std::cerr << "Terminating.";
		exit(1);
	}
	double xmin, ymin, xmax, ymax;
	std::tie(xmin, ymin, xmax, ymax) = GetCoordinateBounds();
	int xresolution = (xmax - xmin + 2) * 30, yresolution = (ymax - ymin + 2)
			* 30;

	svgfile << "<svg width=\"" << xresolution << "\" height=\"" << yresolution
			<< "\" xmlns=\"http://www.w3.org/2000/svg\">" << std::endl;
	svgfile << "<g transform=\"translate(" << (1 - xmin) * 30 << ","
			<< yresolution - (1 - ymin) * 30 << ") scale(1,-1)\">" << std::endl;
	svgfile << "<rect x=\"" << (xmin - 1) * 30 << "\" y=\"" << (ymin - 1) * 30
			<< "\" width=\"" << xresolution << "\" height=\"" << yresolution
			<< "\" fill=\"white\"/>" << std::endl;

	for (int i = 0; i < vertices_; ++i) {
		for (const auto& edge : adjacencylist_[i]) {
			if (edge.first < i) {
				svgfile << edge.second->SVGPrintString() << "\n";
			}
		}
	}
	svgfile << "</g>" << std::endl;
	svgfile << "</svg>" << std::endl;
}
