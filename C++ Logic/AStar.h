#ifndef ASTAR_H
#define ASTAR_H

#include "Search.h"
#include <queue>

class AStar : public Search{
public:
    AStar();
    AStar(Puzzle p);
    Puzzle run(void);

private:
    std::priority_queue<Puzzle, std::vector<Puzzle>, Puzzle::compare_heuristic_distance> frontier;
};


#endif //ASTAR_H
