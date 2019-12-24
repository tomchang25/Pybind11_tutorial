#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <vector>

using namespace std;

class Board{
private:
    int random_index_generate();
    int new_random_element();

public:
    const int MAX = 65536;
    int board [4][4]={{0}};
    int step;
    int score;

    Board();
    int is_win();
    int game_over();

    //show game board
    void display();
    vector<vector<int>> get_board();
    vector<vector<int>> get_code();

    //insert random element
    void add_element();
    //move functions
    int move(int);
    void move_left();
    void move_right();
    void move_up();
    void move_down();
};