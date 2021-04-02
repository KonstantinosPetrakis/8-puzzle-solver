#ifndef API_H
#define API_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "Puzzle.h"
#include "DFS.h"
#include "BFS.h"
#include "BestFS.h"
#include "AStar.h"

#define instruction_file "instruction.txt"
#define data_file "data.txt"

/*
    Here is the communication "protocol" between the two ends.

    Client, runs server - "AI.exe" everytime he wants an instruction executed, any data needed is passed through data file.
    Server executed the instruction and then terminates.

    Instructions:
        run_dfs
        run_bfs
        run_bestfs
        run_astar

    Data:
        From Python ("client" side):
            data = 1 2 3 4 5 6 7 8 9 // Where each number is the tale in the corresponding position.
        From C++ ("server" side):
            if instruction == any_run_method:
                if solution:
                    data = name time solution_length frontier_size states_expanded step1,step2,step3,...,stepn
                else:
                    data = none
*/

// Communication Methods

std::string read_instruction(void);
std::string read_data(void);
void write_data(std::string data);
void insert_data(void);

// Instruction Execution Methods
void execute_instruction(void);


#endif //BFS_CPP_API_H
