#include <algorithm>
#include <cmath>

#include "grid_route_planner.h"

RoutePlanner::RoutePlanner(Grid &grid_model, Node *start, Node *goal)
  : model(grid_model), start_node(start), end_node(goal) {}

void RoutePlanner::CalculateHValue(Node *node) {
    node->h_value = node->distance(*end_node);
}

void RoutePlanner::AddNeighbors(Node *current_node) {
    // Position deltas to search for neighboring cells
    static const int DX[4] = {1, -1, 0, 0};
    static const int DY[4] = {0, 0, 1, -1};
    // Lambda to wrap around grid edges
    auto wrap = [](int v, int max) {
        return (v % max + max) % max;
    };
    // Add neighbours (wrapping around)
    for (int k = 0; k < 4; ++k) {
        int nx = wrap(current_node->x + DX[k], (int)model.Width());
        int ny = wrap(current_node->y + DY[k], (int)model.Height());

        Node *neigh = &model.At(nx, ny);

        if (!neigh->visited) {
            neigh->parent = current_node;
            neigh->g_value = current_node->g_value + current_node->distance(*neigh);
            CalculateHValue(neigh);
            neigh->visited = true;
            open_list.push_back(neigh);
        }
    }
}

Node *RoutePlanner::NextNode() {
    if (open_list.empty()) return nullptr;
    // Sort open list by descending f value using a Lambda expression
    sort(open_list.begin(), open_list.end(), [](Node* n1, Node* n2) -> bool
    {
        return (n1->g_value + n1->h_value) > (n2->g_value + n2->h_value);
    });

    Node* best = open_list.back();  // smallest f-value
    open_list.pop_back();

    return best;
}

std::vector<Node*> RoutePlanner::ConstructFinalPath(Node *current_node) {
    // Create path_found vector
    std::vector<Node*> path_found;
    // While there are still parent nodes (this could also be done checking if start node is reached)
    Node *np = current_node; // Copy to keep current node as last, might not be desired
    while(np->parent != nullptr){
        // Populate path from end to start
        path_found.push_back(np);
        // Repoint
        np = np->parent;
    }
    // Add start node (has no parent)
    path_found.push_back(np);
    // Order path from start to end and scale distance
    std::reverse(path_found.begin(), path_found.end());

    return path_found;
}


// Write the A* Search algorithm here.
void RoutePlanner::AStarSearch() {
    // Init
    Node *current_node = start_node;
    current_node->g_value = 0.0f;
    current_node->visited = true;
    CalculateHValue(current_node);
    open_list.emplace_back(start_node);
    // Search while list is open
    while(open_list.size() > 0){
        // Select next node
        current_node = NextNode();
        // Check if the current node is null (catch unexpected case)
        if (current_node == nullptr) {
            std::cerr << "Error: current_node is null. Path planning failed." << "\n";
            return;
        }
        // Check if the next node is the end one
        if (current_node == end_node){
            // If so, construct final path
            plan = ConstructFinalPath(current_node);
            return;
        }
        // Otherwise, keep adding neighbors
        AddNeighbors(current_node);
    }
    std::cerr << "Error: No path found from start to end nodes.";
}