#include <algorithm>
#include <fstream>
#include <iostream>
#include "labyrinth.h"

Labyrinth::Labyrinth(int vertices, int startvertex, int endvertex)
    : vertices_(vertices), startvertex_(startvertex), endvertex_(endvertex) {}

void Labyrinth::InitialiseGraph() {
  adjacencylist_.clear();
  adjacencylist_.resize(vertices_);
}

void Labyrinth::GenerateLabyrinth(DepthFirstSearch* algorithm) {
  auto minimumspanningtree =
      algorithm->MinimumSpanningTree(vertices_, adjacencylist_);
  RemoveBorders(minimumspanningtree);
}

void Labyrinth::RemoveBorders(const std::vector<std::pair<int, int>>& edges) {
  for (const auto& edge : edges) {
    int u = edge.first, v = edge.second;
    for (int i = 0; i < (int)adjacencylist_[u].size(); ++i) {
      if (adjacencylist_[u][i].first == v) {
        adjacencylist_[u].erase(adjacencylist_[u].begin() + i);
        break;
      }
    }
    for (int i = 0; i < (int)adjacencylist_[v].size(); ++i) {
      if (adjacencylist_[v][i].first == u) {
        adjacencylist_[v].erase(adjacencylist_[v].begin() + i);
        break;
      }
    }
  }
}

void Labyrinth::PrintLabyrinthSVG(const std::string& outputprefix) const {
  std::ofstream svgfile(outputprefix + ".svg");
  if (!svgfile) {
    std::cerr << "Error opening " << outputprefix << ".svg for writing.\n";
    std::cerr << "Terminating.";
    exit(1);
  }
  double xmin, ymin, xmax, ymax;
  std::tie(xmin, ymin, xmax, ymax) = GetCoordinateBounds();
  int xresolution = (xmax - xmin + 2) * 30,
      yresolution = (ymax - ymin + 2) * 30;

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
