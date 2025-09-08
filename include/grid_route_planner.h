#ifndef GRID_ROUTE_PLANNER_H
#define GRID_ROUTE_PLANNER_H

#include <iostream>
#include <vector>
#include <string>

#include <grid.h>

class RoutePlanner {
  public:
    RoutePlanner(Grid &grid_model, Node *start_node, Node *goal_node);
    
    // Public methods
    void CalculateHValue(Node *node);
    void AddNeighbors(Node *current_node);
    std::vector<Node*> ConstructFinalPath(Node *current_node);
    Node *NextNode();
    void AStarSearch();
    const std::vector<Node*>& GetPlan() const { return plan; }

  private:
    Grid &model;
    std::vector<Node*> open_list;
    Node *start_node = nullptr;
    Node *end_node = nullptr;
    std::vector<Node*> plan;
};

#endif