//
// Created by Ira Evetts on 1/21/26.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H



class GameBoard {
    public:
    GameBoard(int width,int height,char behavior=0);
    ~GameBoard();
    int return_height() const;
    int return_width() const;
    int get_board_buffer_index(int current_x, int current_y);

    bool return_cell_value(int x,int y);
    void set_cell_value(int x, int y, bool value);

    bool return_neighbor_cell_value();


private:
    int board_width,board_height;
    char board_behavior;
    bool* board;


};



#endif //GAME_BOARD_H
