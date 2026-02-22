//
// Created by Ira Evetts on 1/21/26.
//

#include "GameBoard.h"

#include <iostream>

GameBoard::GameBoard(int width, int height, char behavior) {
    board_width = width;
    board_height = height;
    board_behavior = behavior;
    board = new float[board_width * board_height];
    current_index = 0;
}
GameBoard::~GameBoard() {
    delete [] board;
}



int GameBoard::return_height() const {return board_height;}
int GameBoard::return_width() const {return board_width;}

int GameBoard::return_board_buffer_index( int current_x,  int current_y) const {
    current_x=((current_x % board_width) + board_width) % board_width;
    current_y=((current_y % board_height) + board_height) % board_height;
    return (current_y * board_width + current_x)  ;
}


float GameBoard::return_cell_value(const int x, const int y) const {
    const int position= return_board_buffer_index(x,y);
    return(board[position]);
}
void GameBoard::set_current_index(int x,int y) {
    current_index= return_board_buffer_index(x,y);
}
float GameBoard::return_next_cell_value() {
    current_index += 1;
    return(board[current_index-1]);

}


void GameBoard::set_cell_value(const int x, const int y, const float value) const {
    board[return_board_buffer_index(x,y)]=value;
}
void GameBoard::set_next_cell_value(const float value) {
    board[current_index]=value;
    current_index += 1;

}
void GameBoard::add_cell_value(const int x, const int y, const float value) const {
    board[return_board_buffer_index(x,y)]+=value;
}


float GameBoard::return_neighbor_cell_value(const int current_x, const int current_y, const int x_offset, const int y_offset) const {
    return return_cell_value(current_x + x_offset,current_y + y_offset);
}




