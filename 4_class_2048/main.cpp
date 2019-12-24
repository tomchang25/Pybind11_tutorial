#include "Game2048.h"

int main(){
    char ch;
    //initialize board
    Board board = Board();
    
    while (1)
    {
        if(board.game_over()){
            cout<<"~~~GAME OVER~~~"<<endl;
            exit(2);
        }

        board.display();
        //show current scores
        cout<<"score: "<<board.score<<endl;
        cout<<"step: "<<board.step<<endl;

        cin>>ch;
        switch (ch) {
            case 'w':
                board.move_up();
                break;
            case 's':
                board.move_down();
                break;
            case 'a':
                board.move_left();
                break;
            case 'd':
                board.move_right();
                break;
            case 'q':
                exit(1);
            default:
                break;
        }
    }
    return 0;
}

