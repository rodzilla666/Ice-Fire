#include "floatingBlock.h"
#include <iostream>
using namespace std;

Block::Block(int x, int y, BlockType t) {
    x_pos = x;
    y_pos = y;
    type = t;
    if (type == good)
    {
        states[0].hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[0].hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    setState(moving_right);
    /*else
    {
        states[0].hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\boy_standing_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[0].hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\boy_standing_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }*/
}

Block::Block(){
    setState(moving_right);
    x_pos=400;
    y_pos=250;
    type=good;
}


void Block::update(HDC hdc){
}

void Block::moveLeft(HDC hdc){
    setState(moving_left);
}


void Block::moveRight(HDC hdc){
    setState(moving_right);
}

void Block::setState(BlockState s){
    state=s;
    hbm = states[state].hbm;
    hbmMask = states[state].hbmMask;

    BITMAP bitmap;
    GetObject(hbm, sizeof(BITMAP), &bitmap);
    width=bitmap.bmWidth/1;
    height=bitmap.bmHeight/1;
}

