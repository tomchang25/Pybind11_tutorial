/*
 @author Zihan Qi
  @version 1.0 10/27/2017

 @author Greysuki
 @version 1.c 12/17/2019
 */
#include "Game2048.h"
using namespace std;

Board::Board(){
    srand((unsigned)time(NULL));

    int index_i1, index_j1, index_i2, index_j2;

    while(1){
        index_i1 = random_index_generate();
        index_j1 = random_index_generate();
        index_i2 = random_index_generate();
        index_j2 = random_index_generate();
        if(index_i1==index_i2 && index_j1==index_j2){
            continue;
        }
        else
            break;
    }
    board[index_i1][index_j1] = new_random_element();
    board[index_i2][index_j2] = new_random_element();

    score = 0;
    step = 0;
}

int Board::random_index_generate(){
    int random_index = rand() % 4;
    return random_index;
}

int Board::new_random_element(){
    int random_element = rand() % 10;
    random_element = (random_element==0) ? 4 : 2;
    return random_element;
}

int Board::is_win(){
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            if(board[i][j]==MAX){
                return 1;
            }
        }
    }
    return 0;
}

int Board::game_over(){
    int is_game_over = 1;
    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(board[i][j]==0 || board[i][j+1]==0 || board[i][j] == board[i][j+1]){
                is_game_over = 0;
                break;
            }
        }
    }
    for(int j=0; j<4; j++){
        for(int i=0; i<3; i++){
            if(board[i][j]==0 || board[i+1][j]==0 || board[i][j] == board[i+1][j]){
                is_game_over = 0;
                break;
            }
        }
    }
    return is_game_over;
}
//show game board
void Board::display(){
    for(int i=0; i<4; i++){
        cout << "|-----------------------|" << endl;


        for (int j = 0; j < 4; j++)
        {
            cout << "|";
            if(board[i][j] != 0){
                unsigned digit = floor(log10(board[i][j]) + 1); 
                if(digit == 4){
                    cout << " " << board[i][j];
                }
                else if (digit == 3){
                    cout << " " << board[i][j] << " ";
                }
                else if(digit == 2){
                    cout << "  " << board[i][j] << " ";
                }
                else if(digit == 1){
                    cout << "  " << board[i][j] << "  ";
                }
            }
            else{
                cout << "     ";
            }
        }
        cout << "|" << endl;

    }
    cout << "|-----------------------|" << endl;
}

vector<vector<int>> Board::get_board(){
    vector<vector<int>> vec = {
        vector<int>(begin(board[0]), end(board[0])),
        vector<int>(begin(board[1]), end(board[1])),
        vector<int>(begin(board[2]), end(board[2])),
        vector<int>(begin(board[3]), end(board[3])),
    };

    return vec;
}

vector<vector<int>> Board::get_code(){
    vector<vector<int>> vec = {
        vector<int>(begin(board[0]), end(board[0])),
        vector<int>(begin(board[1]), end(board[1])),
        vector<int>(begin(board[2]), end(board[2])),
        vector<int>(begin(board[3]), end(board[3])),
    };

    for (unsigned i = 0; i < vec.size();i++)
    {
        for (unsigned j = 0; j < vec.size();j++){
            if (vec[i][j] != 0){
                vec[i][j] = log2(vec[i][j]);
            }
        }
    }

    return vec;
}

//insert random element
void Board::add_element(){
    int index_i3, index_j3;
    int flag=0;
    while(1){
        if(flag==1)break;
        index_i3 = random_index_generate();
        index_j3 = random_index_generate();
        if(board[index_i3][index_j3]==0){
            board[index_i3][index_j3] = new_random_element();
            flag=1;
        }
    }
}

//move functions
int Board::move(int op){
    int pre_score = score;
    if (op == 0)
    {
        move_up();
    }
    else if (op == 1){
        move_right();
    }
    else if (op == 2){
        move_down();
    }
    else if (op == 3){
        move_left();
    }

    return score - pre_score;
}

void Board::move_left(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=0; j<4; j++)
        {
            if (n==board[i][j] && n!=0){
                board[i][prev] = 2*n;
                board[i][j] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[i][j]!=0){
                n = board[i][j];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<3; k++){
                if(board[i][k]==0 && board[i][k+1]!=0){
                    board[i][k]=board[i][k]^board[i][k+1];
                    board[i][k+1]=board[i][k]^board[i][k+1];
                    board[i][k]=board[i][k]^board[i][k+1];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
}

void Board::move_right(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=3; j>=0; j--)
        {
            if (n==board[i][j] && n!=0){
                board[i][prev] = 2*n;
                board[i][j] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[i][j]!=0){
                n = board[i][j];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=3; k>0; k--){
                if(board[i][k]==0 && board[i][k-1]!=0){
                    board[i][k]=board[i][k]^board[i][k-1];
                    board[i][k-1]=board[i][k]^board[i][k-1];
                    board[i][k]=board[i][k]^board[i][k-1];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
}

void Board::move_up(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=0; j<4; j++)
        {
            if (n==board[j][i] && n!=0){
                board[prev][i] = 2*n;
                board[j][i] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[j][i]!=0){
                n = board[j][i];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=0; k<3; k++){
                if(board[k][i]==0 && board[k+1][i]!=0){
                    board[k][i]=board[k][i]^board[k+1][i];
                    board[k+1][i]=board[k][i]^board[k+1][i];
                    board[k][i]=board[k][i]^board[k+1][i];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
}

void Board::move_down(){
    int flag=0;
    for(int i=0; i<4; i++){
        int n=0;
        int prev=0;
        for (int j=3; j>=0; j--)
        {
            if (n==board[j][i] && n!=0){
                board[prev][i] = 2*n;
                board[j][i] = 0;
                score+=2*n;
                n = 0;
                flag++;
                continue;
            }
            if (board[j][i]!=0){
                n = board[j][i];
                prev = j;
            }
        }
    }
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            for(int k=3; k>0; k--){
                if(board[k][i]==0 && board[k-1][i]!=0){
                    board[k][i]=board[k][i]^board[k-1][i];
                    board[k-1][i]=board[k][i]^board[k-1][i];
                    board[k][i]=board[k][i]^board[k-1][i];
                    flag++;
                }
            }
        }
    }
    if(flag!=0){
        add_element();
        step++;
    }
}

