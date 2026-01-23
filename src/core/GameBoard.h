//
// Created by Ira Evetts on 1/21/26.
//

#ifndef GAME_BOARD_H
#define GAME_BOARD_H



class GameBoard {
    public:
    GameBoard(int width,int height,char behavior=0);
    ~GameBoard();
    unsigned char* board;
    int return_height() const;
    int return_width() const;

    int return_board_buffer_index(int current_x, int current_y) const;

    void set_current_index(int x,int y);
    void set_next_cell_value(unsigned char value);

    unsigned char return_cell_value(int x,int y) const;

    unsigned char return_next_cell_value();

    void set_cell_value(int x, int y, unsigned char value) const;

    unsigned char return_neighbor_cell_value(int current_x, int current_y,int x_offset,int y_offset) const;


private:
    int board_width,board_height;
    char board_behavior;
    int current_index;



};



#endif //GAME_BOARD_H
