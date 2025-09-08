#include "grid.h"

// ------------------ Node ------------------

int Node::distance(Node other_node) const {
    // Manhattan distance
    return std::abs(x - other_node.x) + std::abs(y - other_node.y);
}

// ------------------ Grid ------------------

Grid::Grid(std::size_t w, std::size_t h) : width(w), height(h) {
  // allocate width × height nodes
  cells.assign(width, std::vector<Node>(height));

  // initialize coordinates
  for (std::size_t x = 0; x < width; ++x) {
    for (std::size_t y = 0; y < height; ++y) {
      cells[x][y].x = static_cast<int>(x);
      cells[x][y].y = static_cast<int>(y);
    }
  }
}

void Grid::Reset() {
  for (std::size_t x = 0; x < width; ++x) {
    for (std::size_t y = 0; y < height; ++y) {
      Node &n = cells[x][y];
      n.state = State::kEmpty;
      n.h_value = 0;
      n.g_value = 0;
      n.visited = false;
      n.parent = nullptr;
      n.neighbors.clear();
    }
  }
}

void Grid::MarkFood(int x, int y) {
  if (x >= 0 && y >= 0 &&
      x < static_cast<int>(width) &&
      y < static_cast<int>(height)) {
    cells[x][y].state = State::kFinish;
  }
}

void Grid::MarkObstacle(int x, int y) {
  if (x >= 0 && y >= 0 &&
      x < static_cast<int>(width) &&
      y < static_cast<int>(height)) {
    cells[x][y].state = State::kObstacle;
  }
}
