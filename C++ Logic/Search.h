#ifndef SEARCH_H
#define SEARCH_H

#include <unordered_set>
#include <deque>
#include "Puzzle.h"


class Search{
public:
    // Constructors
    Search();
    Search(Puzzle p);

    // Main method
    virtual Puzzle run() = 0;

    // Getters
    unsigned int get_visit_counter(void) const;
    unsigned int get_mem_counter(void) const;
    double get_search_time(void) const;
    std::string get_name(void) const;
    std::string to_string(void) const;

protected:
    // Used for printing
    std::string name;

    // Functional properties
    Puzzle root_p;
    Puzzle solution;
    std::unordered_set<Puzzle, Puzzle::Hash> closed_set;
    std::deque<Puzzle> frontier;

    // Benchmark properties
    unsigned int mem_counter;
    unsigned int visit_counter;
    double search_time;
};

#endif // SEARCH_H
