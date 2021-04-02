#ifndef BFS_H
#define BFS_H

#include "Search.h"

class BFS : public Search{
public:
    BFS();
    BFS(Puzzle p);
    Puzzle run(void);
};


#endif //BFS_H
