#ifndef BESTFS_H
#define BESTFS_H

#include "Search.h"
#include "queue"

class BestFS : public Search{
public:
    BestFS();
    BestFS(Puzzle p);
    Puzzle run(void);

private:
    std::priority_queue<Puzzle, std::vector<Puzzle>, Puzzle::compare_heuristic> frontier;
};

#endif //BESTFS_H
