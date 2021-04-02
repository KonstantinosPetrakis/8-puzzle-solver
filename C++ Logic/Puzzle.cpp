#include "Puzzle.h"

//Declare static members/functions (Solution description)

Puzzle Puzzle::initialize_solution(void){
    /**
    This method returns the solution, it's used to initialize the var solution.
    @return the puzzle object, solution.
    */

    Puzzle p;
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++){
            p.boxes[i][j] = i * WIDTH + j + 1; // Something is wrong here
        }
    }
    return p;
}

Puzzle Puzzle::solution = Puzzle::initialize_solution();

// Non static class code
Puzzle::Puzzle(){
    length = 0;
    father = nullptr;
}

Puzzle::Puzzle(std::string data) : Puzzle(){
    set_boxes(data);
}

/**
 This method expands the current state.
 @return a vector containing the children states.
*/
std::vector<Puzzle> Puzzle::expand(void) const{
    std::vector<Puzzle> children;

    if (can_go_up()){
        children.push_back(go_up());
    }
    if (can_go_down()){
        children.push_back(go_down());
    }
    if (can_go_left()){
        children.push_back(go_left());
    }
    if (can_go_right()){
        children.push_back(go_right());
    }
    return children;
}

// Getters

/**
 This method returns the solution that mast be found by some search algorithm.
 * @return the puzzle object mentioned above.
 */
Puzzle Puzzle::get_solution(void) const{
    return solution;
}

/**
 This method returns boxes array (space = WIDTH * HEIGHT).
 @return
*/
unsigned int** Puzzle::get_boxes(void) const{
    // Create a 2d pointer array
    unsigned int **copy_boxes = new unsigned int *[WIDTH];
    for (int i=0; i<WIDTH; i++){
        copy_boxes[i] = new unsigned int [HEIGHT];
    }

    // Copy the values in it
    for (int i=0; i<WIDTH; i++){
        for (int j=0; j<HEIGHT; j++){
            copy_boxes[i][j] = boxes[i][j];
        }
    }
    return copy_boxes;
}

/**
 This method follows the father's path until the starting state.
 @return a queue containing all the puzzles from the starting state to the ending state.
*/
std::stack<Puzzle> Puzzle::get_path(void) const{
    std::stack<Puzzle> path;
    Puzzle node = *this;

    path.push(node);
    while (node.father != nullptr){
        path.push(*node.father);
        node = *node.father;
    }

    return path;
}

/**
 This method returns the description of actions to be followed to get to that state from the starting state.
 @return the string mentioned above.
*/
std::string Puzzle::get_description(void) const{
    std::stack<Puzzle> s = get_path();
    std::string desc;

    while (!s.empty()){
        desc += s.top().description + ",";
        s.pop();
    }
    return desc;
}

/**
 * This method checks the length of that state, how many action it takes to get to it from the starting state.
 * @return the action counter.
 */
unsigned int Puzzle::get_length() const {
    return length; // length was tracked down because it was costy procedure and A* was calling it a lot.
}

// Setters

/**
 * This method is is used to set the boxes of the puzzle. Although only works for 3x3 puzzles (implemented to work with API).
 * @param boxes a string containing non separated digits of the tales.
 */
void Puzzle::set_boxes(std::string str_boxes) {
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++) {
            boxes[i][j] = (int) str_boxes.at(i * WIDTH + j) - 48;
            if (((unsigned int) str_boxes.at(i * WIDTH + j) - 48) == SPACE){ //Some ascii logic right here.
                space_location[0] = i; space_location[1] = j;
            }
        }
    }
}

// Operators

bool Puzzle::operator ==(Puzzle const &p) const{
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++){
            if (boxes[i][j] != p.boxes[i][j]){
                return false;
            }
        }
    }
    return true;
}

std::ostream& operator <<(std::ostream &os, const Puzzle &p){
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++){
            os << std::setw(3);
            if (p.boxes[i][j] != SPACE){
                os << p.boxes[i][j] << " ";
            }
            else{
                os << " " << " ";
            }
        }
        os << std::endl;
    }
    return os;
}

bool Puzzle::operator<(const Puzzle &p) const {
    return heuristic() < p.heuristic();
}

bool Puzzle::operator>(const Puzzle &p) const {
    return heuristic() > p.heuristic();
}

// Utility methods

/**
 This method initializes the Puzzle in a random sequence. <b> Careful! </b> Sometimes it might be unsolvable!
*/
void Puzzle::randomize_puzzle(void){
    unsigned int temp, r_i, r_j;
    srand(time(0));

    // Enter all the digits inside boxes array in the physical order
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++){
            boxes[i][j] = i * WIDTH  + j + 1;
        }
    }
    space_location[0] = WIDTH - 1;
    space_location[1] = HEIGHT - 1;

    // Shuffle the boxes of the array
    for(unsigned int i=0; i<WIDTH; i++){
        for(unsigned int j=0; j<HEIGHT; j++){
            r_i = rand() % WIDTH;
            r_j = rand() % HEIGHT;
            temp = boxes[i][j];
            boxes[i][j] = boxes[r_i][r_j];
            boxes[r_i][r_j] = temp;

            // Check if space location swap occur
            if (space_location[0] == i && space_location[1] == j){
                space_location[0] = r_i;
                space_location[1] = r_j;
            }
            else if (space_location[0] == r_i && space_location[1] == r_j){
                space_location[0] = i;
                space_location[1] = j;
            }
        }
    }
}

/**
 * This method finds a value h that approximates roughly the distance from the solution. h lays between [0, WIDTH*HEIGHT].
 * @return the approximation of distance h (the less the better).
 */
unsigned int Puzzle::heuristic(void) const {
    unsigned int h = WIDTH * HEIGHT;
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++){
            if (boxes[i][j] == i * WIDTH + j + 1){ // digit is in correct place.
                h--;
            }
        }
    }

    return h;
}

/**
 * This method finds an heuristic value that takes in account the state's length.
 * @return the heuristic value mentioned above.
 */
unsigned int Puzzle::heuristic_distance() const {
    return heuristic() + get_length();
}

/**
 * This method compares two puzzles using heuristic method.
 * @return whether p1's heuristic is greater than p2 or not.
 */
bool Puzzle::compare_heuristic::operator()(const Puzzle &p1, const Puzzle &p2) {
    return p1.heuristic() > p2.heuristic();
}

/**
 * This method compares two puzzles using heuristic_distance..
 * @return whether p1's heuristic_distance is greater than p2 or not.
 */
bool Puzzle::compare_heuristic_distance::operator()(const Puzzle &p1, const Puzzle &p2) {
    return p1.heuristic_distance() > p2.heuristic_distance();
}

/**
 This method hashes the state into a key.
 @return the hash key.
*/
size_t Puzzle::Hash::operator()(const Puzzle &t) const{
    std::hash<std::string> string_hasher;
    std::string s;
    for (unsigned int i=0; i<WIDTH; i++){
        for (unsigned int j=0; j<HEIGHT; j++){
            s += std::to_string(t.boxes[i][j]) + ",";
        }
    }
    return string_hasher(s);
}

// Expansion ability methods

/**
 This method checks whether the space in the puzzle can move up.
 @return a boolean value which corresponds to the above statement.
*/
bool Puzzle::can_go_up(void) const{
    return space_location[0] > 0;
}

/**
 This method checks whether the space in the puzzle can move up.
 @return a boolean value which corresponds to the above statement.
*/
bool Puzzle::can_go_down(void) const{
    return space_location[0] < HEIGHT - 1;
}

/**
 This method checks whether the space in the puzzle can move up.
 @return a boolean value which corresponds to the above statement.
*/
bool Puzzle::can_go_left(void) const{
    return space_location[1] > 0;
}

/**
 This method checks whether the space in the puzzle can move up.
 @return a boolean value which corresponds to the above statement.
*/
bool Puzzle::can_go_right(void) const{
    return space_location[1] < WIDTH - 1;
}

//Expansion Methods

/**
 This method expands the current state by making the space in puzzle go up.
 @return the child of the state.
*/
Puzzle Puzzle::go_up(void) const{
    Puzzle cpy = *this;
    cpy.boxes[space_location[0]][space_location[1]] = cpy.boxes[space_location[0]-1][space_location[1]];
    cpy.boxes[space_location[0]-1][space_location[1]] = SPACE;
    cpy.space_location[0]--;
    cpy.father = this;
    cpy.length = this->length + 1;
    cpy.description = "up";

    return cpy;
}

/**
 This method expands the current state by making the space in puzzle go down.
 @return the child of the state.
*/
Puzzle Puzzle::go_down(void) const{
    Puzzle cpy = *this;

    cpy.boxes[space_location[0]][space_location[1]] = cpy.boxes[space_location[0]+1][space_location[1]];
    cpy.boxes[space_location[0]+1][space_location[1]] = SPACE;
    cpy.space_location[0]++;
    cpy.father = this;
    cpy.length = this->length + 1;
    cpy.description = "down";

    return cpy;
}

/**
 This method expands the current state by making the space in puzzle go left.
 @return the child of the state.
*/
Puzzle Puzzle::go_left(void) const{
    Puzzle cpy = *this;

    cpy.boxes[space_location[0]][space_location[1]] = cpy.boxes[space_location[0]][space_location[1]-1];
    cpy.boxes[space_location[0]][space_location[1]-1] = SPACE;
    cpy.space_location[1]--;
    cpy.father = this;
    cpy.length = this->length + 1;
    cpy.description = "left";

    return cpy;
}

/**
 This method expands the current state by making the space in puzzle go right.
 @return the child of the state.
*/
Puzzle Puzzle::go_right(void) const{
    Puzzle cpy = *this;

    cpy.boxes[space_location[0]][space_location[1]] = cpy.boxes[space_location[0]][space_location[1]+1];
    cpy.boxes[space_location[0]][space_location[1]+1] = SPACE;
    cpy.space_location[1]++;
    cpy.father = this;
    cpy.length = this->length + 1;
    cpy.description = "right";

    return cpy;
}

