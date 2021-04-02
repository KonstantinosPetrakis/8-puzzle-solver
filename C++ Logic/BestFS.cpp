#include "BestFS.h"

BestFS::BestFS() : Search(){
    name = "BestFS";
}

BestFS::BestFS(Puzzle p) : Search(p){
    name = "BestFS";
}

/**
 This method runs BestFS on the given root state p (initial state).
 @return the first solution (final state) it finds. Or some trash if solution can't be found.
*/
Puzzle BestFS::run(void){
    Puzzle p;
    clock_t t0 = clock();

    frontier.push(root_p);

    while (!frontier.empty()){
        // Get the first state from the frontier.
        p = frontier.top();
        frontier.pop();

        // Check if it's inside close set.
        if (closed_set.count(p)) {
            continue;
        }

        // Check if we found the solution.
        if (p == p.get_solution()) {
            break;
        }

        // Insert state in the closed set.
        const Puzzle &new_p = *closed_set.insert(p).first;

        // Expand the state and put its children in the frontier.
        for (Puzzle &child: new_p.expand()) {
            frontier.push(child);
        }

        // Benchmark checks
        visit_counter++;
        if (frontier.size() > mem_counter) mem_counter = frontier.size();
    }

    clock_t t1 = clock();
    search_time = double(t1 - t0) / CLOCKS_PER_SEC;
    solution = p;

    return p;
}