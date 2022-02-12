#pragma once
#include <windows.h>
#include <vector>

enum BlockState { moving_right=0, moving_left };
enum BlockType { good, bad };

struct BlockSprite {
    HBITMAP hbm;
    HBITMAP hbmMask;
    BlockSprite(HBITMAP h, HBITMAP m) : hbm{ h }, hbmMask{m} {}
    BlockSprite(){}
};

class Block{
public:
    HBITMAP hbm;
    HBITMAP hbmMask;
    int x_pos;
    int y_pos;
    int dy=1;
    int dx=1;
    int width;
    int height;
    int x_animation=0;
    int y_animation=0;
    bool gravityEnabled=false;
    int gravity=8;
    BlockType type;
    BlockState state=moving_right;
    std::vector<BlockSprite> states{7};

    Block(int x, int y, BlockType t);
    Block();
    void update(HDC hdc); // animation, gravity
    void moveLeft(HDC hdc);
    void moveRight(HDC hdc);
    void setState(BlockState s);
};

