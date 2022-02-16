#pragma once
#include <windows.h>
#include <vector>
#define FLOOR 16777215
#define WALL 0
#define LAVA 8168
#define WATER 16352555
enum State { standing_right=0, standing_left, jumping_right,
                jumping_left, running_right, running_left, dead_right, dead_left };
enum PlayerType { red, blue };

struct Sprite {
    HBITMAP hbm=NULL;
    HBITMAP hbmMask=NULL;
    Sprite(HBITMAP h, HBITMAP m) : hbm{ h }, hbmMask{m} {}
    Sprite(){}
};

class Player{
public:
    HBITMAP hbm;
    HBITMAP hbmMask;
    int x_pos;
    int y_pos;
    int dy=5;
    int dx=5;
    int width;
    int height;
    int x_animation=0;
    int y_animation=0;
    bool gravityEnabled=true;
    int gravity=8;
    int jumping=0;
    bool standingOnWhiteBlock = true;
    int diamondsCollected = 0;
    PlayerType type;
    State state=standing_right;
    State lastState=running_right;
    std::vector<int> jumpVal{20,18,16,13,10,7,5,4,4,3,3,2,1};
    std::vector<Sprite> states{7};

    Player(int x, int y, PlayerType t);
    Player();
    void update(HDC hdc); // animation, gravity
    void moveLeft(HDC hdc);
    void moveRight(HDC hdc);
    void jump(HDC hdc);
    bool isJumping();
    void setState(State s);
    void addDiamond();
};
