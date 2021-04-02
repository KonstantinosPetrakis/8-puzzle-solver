#ifndef PUZZLE_H
#define PUZZLE_H

// Libraries
#include <iostream>
#include <iomanip>
#include <vector>
#include <stack>
#include <string>
#include <ctime>
#include <cmath>

// Constants
#define WIDTH 3
#define HEIGHT 3
#define SPACE WIDTH * HEIGHT

class Puzzle{
public:
    Puzzle();
    Puzzle(std::string data);

    // Expansion methods
    std::vector<Puzzle> expand() const;

    // Getters
    unsigned int** get_boxes(void) const;
    std::string get_description(void) const;
    unsigned int get_length(void) const;
    std::stack<Puzzle> get_path(void) const; // Let's call it pseudo-getter.
    Puzzle get_solution(void) const;

    // Setters
    void set_boxes(std::string str_boxes);

    // Operators
    bool operator ==(Puzzle const& p) const;
    bool operator <(Puzzle const& p) const; //Uses heuristic method
    bool operator >(Puzzle const& p) const; //Uses heuristic method
    friend std::ostream& operator <<(std::ostream& os, const Puzzle& p);

    // Utility methods and stuff
    unsigned int heuristic(void) const;
    unsigned int heuristic_distance(void) const;
    void randomize_puzzle();

    class Hash{
    public:
        size_t operator()(const Puzzle &t) const;
    };

    struct compare_heuristic{
        bool operator()(Puzzle const &p1, Puzzle const &p2);
    };

    struct compare_heuristic_distance{
        bool operator()(Puzzle const &p1, Puzzle const &p2);
    };

private:
    // Solution description
    static Puzzle initialize_solution();
    static Puzzle solution;

    // State description properties
    unsigned int boxes[WIDTH][HEIGHT]; // WIDTH * HEIGHT + 1 used for space
    unsigned int space_location[2]; // Saved for optimisation

    // Path description properties
    std::string description;
    unsigned int length;
    Puzzle const* father;

    // Expansion ability methods
    bool can_go_up(void) const;
    bool can_go_down(void) const;
    bool can_go_left(void) const;
    bool can_go_right(void) const;

    // Expansion methods
    Puzzle go_up(void) const;
    Puzzle go_down(void) const;
    Puzzle go_left(void) const;
    Puzzle go_right(void) const;
};

#endif // PUZZLE_H
