#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
#include "circularlabyrinth.h"

CircularLabyrinth::CircularLabyrinth(int size) :
		size_(size) {
	ringnodecount_ = std::vector<int>(size_);
	ringnodeprefixsum_ = std::vector<int>(size_);
	ringnodecount_[0] = 1;
	ringnodeprefixsum_[0] = 0;

	for (int i = 1; i < size_; ++i) {
		ringnodecount_[i] = ringnodecount_[i - 1];
		if (2 * M_PI * i / ringnodecount_[i - 1] > 2)
			ringnodecount_[i] *= 2;
		ringnodeprefixsum_[i] = ringnodeprefixsum_[i - 1]
				+ ringnodecount_[i - 1];
	}
	vertices_ = ringnodecount_.back() + ringnodeprefixsum_.back();
	startvertex_ = ringnodeprefixsum_.back();
	endvertex_ = startvertex_ + ringnodecount_.back() / 2;
}

void CircularLabyrinth::InitialiseGraph() {
	adjacencylist_.clear();
	adjacencylist_.resize(vertices_);

	/** Proper to circular maze **/

	for (int i = 1; i < size_; ++i) {
		for (int j = 0; j < ringnodecount_[i]; ++j) {
			int node = ringnodeprefixsum_[i] + j, nnode;
			std::shared_ptr < CellBorder > ptr;

			nnode = ringnodeprefixsum_[i - 1]
					+ (ringnodecount_[i - 1] * j) / ringnodecount_[i];
			ptr = std::make_shared < ArcBorder
					> (0, 0, i, j * 2 * M_PI / ringnodecount_[i] - M_PI / 2, (j
							+ 1) * 2 * M_PI / ringnodecount_[i] - M_PI / 2);
			adjacencylist_[node].push_back( { nnode, ptr });
			adjacencylist_[nnode].push_back( { node, ptr });

			nnode = ringnodeprefixsum_[i] + ((j + 1) % ringnodecount_[i]);
			double theta = (j + 1) * 2 * M_PI / ringnodecount_[i] - M_PI / 2;
			ptr = std::make_shared < LineBorder
					> (i * cos(theta), i * sin(theta), (i + 1) * cos(theta), (i
							+ 1) * sin(theta));
			adjacencylist_[node].push_back( { nnode, ptr });
			adjacencylist_[nnode].push_back( { node, ptr });

			if (i == size_ - 1 and node != startvertex_
					and node != endvertex_) {
				ptr = std::make_shared < ArcBorder
						> (0, 0, size_, j * 2 * M_PI / ringnodecount_[i]
								- M_PI / 2, (j + 1) * 2 * M_PI
								/ ringnodecount_[i] - M_PI / 2);
				adjacencylist_[node].push_back( { -1, ptr });
			}
		}
	}

	/** ********************** **/
}

std::tuple<double, double, double, double> CircularLabyrinth::GetCoordinateBounds() {
	return std::make_tuple(-size_, -size_, size_, size_);
}

void CircularLabyrinth::GenerateLabyrinth(DepthFirstSearch* algorithm) {
	auto minimumspanningtree = algorithm->MinimumSpanningTree(vertices_,
			adjacencylist_);
	RemoveBorders(minimumspanningtree);
}

void CircularLabyrinth::RemoveBorders(const std::vector<std::pair<int, int>>& edges) {
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

void CircularLabyrinth::PrintLabyrinthSVG(const std::string& outputprefix) {
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
