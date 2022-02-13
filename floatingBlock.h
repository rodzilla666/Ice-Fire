#pragma once
#include <windows.h>
#include <vector>

enum BlockType { good, bad };

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
    BlockType type;

    Block(int x, int y, int xmi, int xma, int ymi, int yma, int dxx, int dyy,  BlockType t);
    Block();
    void update(HDC hdc);
};
