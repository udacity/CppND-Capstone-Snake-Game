#ifndef GRID_H
#define GRID_H

#include <iostream>
#include <vector>

enum class State {kEmpty, kObstacle, kClosed, kPath, kStart, kFinish};

struct Node {
  State state = State::kEmpty;
  int x = 0;
  int y = 0;
  int h_value = 0;
  int g_value = 0;
  bool visited = false;
  Node * parent = nullptr;
  std::vector<Node *> neighbors;

  int distance(Node other_node) const;
};

class Grid {
public:
  Grid(std::size_t w, std::size_t h);

  void Reset();
  void MarkFood(int x, int y);
  void MarkObstacle(int x, int y);

  Node &At(int x, int y) { return cells[x][y]; }
  const std::vector<std::vector<Node>> &Data() const { return cells; }

  std::size_t Width() const { return width; }
  std::size_t Height() const { return height; }

private:
  std::size_t width, height;
  std::vector<std::vector<Node>> cells;
};

#endif