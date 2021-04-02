#include "API.h"


// Communication Methods

/**
 * This method reads the instruction file an gets the first (only) instruction of it.
 * @return the instruction it got.
 */
std::string read_instruction(void){
    std::string instruction;

    std::ifstream instruction_stream(instruction_file);
    if (!instruction_stream){
        std::cout << "Instruction file couldn't be opened." << std::endl;
        return "none";
    }

    instruction_stream >> instruction;
    return instruction;
}

/**
 * This function reads the data out of the data file.
 * @return the data it read.
 */
std::string read_data(void){
    std::string data, word;
    std::ifstream data_stream(data_file);

    if (!data_stream){
        std::cout << "Data file couldn't be opened." << std::endl;
        return "none";
    }

    while (!data_stream.eof()){
        data_stream >> word;
        data += word;
    }
    return data;
}

/**
 * This process writes data to the data file.
 * @param data the data to be written to data file.
 */
void write_data(std::string data){
    std::ofstream data_stream(data_file);
    if (data_stream.is_open()){
        data_stream << data;
    }
    else{
        std::cout << "Couldn't open data file to write." << std::endl;
    }
}

// Instruction Execution Methods

/**
 * This process reads an instruction of the instruction file and it executes it.
 */
void execute_instruction(void){
    std::string instruction = read_instruction();
    std::string data = read_data();

    Puzzle p(data);
    DFS dfs(p); BFS bfs(p); BestFS bestfs(p); AStar astar(p);

    std::map<std::string, Search*> dict = {
            {"run_dfs", &dfs}, {"run_bfs", &bfs},
            {"run_bestfs", &bestfs}, {"run_astar", &astar}};

    dict[instruction]->run();
    write_data(dict[instruction]->to_string());
}


