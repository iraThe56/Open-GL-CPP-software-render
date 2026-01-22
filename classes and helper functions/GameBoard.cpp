//
// Created by Ira Evetts on 1/21/26.
//

#include "GameBoard.h"

#include <iostream>
#include <__ostream/basic_ostream.h>

GameBoard::GameBoard(int width, int height, char behavior) {
    board_width = width;
    board_height = height;
    board_behavior = behavior;
    board = new bool[board_width * board_height];
}
GameBoard::~GameBoard() {
    delete [] board;
}



int GameBoard::return_height() const {return board_height;}
int GameBoard::return_width() const {return board_width;}

int GameBoard::return_board_buffer_index(int current_x, int current_y) {
    current_x=((current_x % board_width) + board_width) % board_width;
    current_y=((current_y % board_height) + board_height) % board_height;
    if (current_y<0)
        std::cout<<"Out of bounds!"<<std::endl;
    return (current_y * board_width + current_x)  ;
}


bool GameBoard::return_cell_value(int x,int y) {
    int position= return_board_buffer_index(x,y);
    return(board[position]);
}


void GameBoard::set_cell_value(int x,int y,bool value) {
    int position= return_board_buffer_index(x,y);
    board[position]=value;
}

bool GameBoard::return_neighbor_cell_value(int current_x, int current_y,int x_offset,int y_offset) {
    int shiftedX = current_x + x_offset;
    int shiftedY = current_y + y_offset;
    return return_cell_value(shiftedX,shiftedY);
}




