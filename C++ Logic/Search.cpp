#include "Search.h"


Search::Search(){
    mem_counter = 0;
    visit_counter = 0;
    search_time = 0;
}

Search::Search(Puzzle p): Search(){
    root_p = p;
}

// Benchmark getters

/**
 @return the maximum number of states that were saved in the frontier at once.
*/
unsigned int Search::get_mem_counter(void) const{
    return mem_counter;
}

/**
 @return the number of states visited (expanded) by the search algorithm.
*/
unsigned int Search::get_visit_counter(void) const{
    return visit_counter;
}

/**
 @return the time run() took to complete in the last search.
*/
double Search::get_search_time(void) const{
    return search_time;
}

/**
 * @return the name of the algorithm used (for printing purposes I guess).
 */
std::string Search::get_name(void) const{
    return name;
}

std::string Search::to_string() const {
    //data = name time solution_length frontier_size states_expanded step1,step2,step3,...,stepn
    std::string s = "";


    s += name + " ";
    s += std::to_string(search_time) + " ";
    s += std::to_string(solution.get_length()) + " ";
    s += std::to_string(mem_counter) + " ";
    s += std::to_string(visit_counter) + " ";
    s += solution.get_description();


    return s;
}