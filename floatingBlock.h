#pragma once
#include <windows.h>
#include <vector>
#include "player.h"

enum BlockType { good, goodBig,bad };

class Block {
public:
    HBITMAP hbm;
    HBITMAP hbmMask;
    int x_pos;
    int y_pos;
    int dy = 1;
    int dx = 1;
    int xMax;
    int xMin;
    int yMax;
    int yMin;
    int width;
    int height;
    int initdx;
    int initdy;
    BlockType type;
    bool isLoop=false;


    Block(int x, int y, int xmi, int xma, int ymi, int yma, int dxx, int dyy,  BlockType t, bool loop);
    Block();
    void update(HDC hdc, Player* boy, Player* girl);
};
