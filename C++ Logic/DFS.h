#ifndef DFS_H
#define DFS_H

#include "Search.h"

class DFS : public Search{
public:
    DFS();
    DFS(Puzzle p);
    Puzzle run(void);
};

#endif // DFS_H
