#pragma once
#include <windows.h>
#define FLOOR 16777215

enum State { standing_right, standing_left, running_left, running_right, jumping_right, jumping_left };
enum PlayerType { red, blue };

class Player{
public:
    HBITMAP hbm;
    HBITMAP hbmMask;
    int x_pos;
    int y_pos;
    int dy=4;
    int dx=4;
    int width;
    int height;
    int x_animation=0;
    int y_animation=0;
    bool gravityEnabled=true;
    int gravity=8;
    int jumping=0;
    PlayerType type;
    State state=standing_right;
    State lastState=running_right;

    Player(int x, int y, PlayerType t);
    Player();
    void update(HDC hdc); // animation, gravity
    void moveLeft(HDC hdc);
    void moveRight(HDC hdc);
    void jump(HDC hdc);
    bool isJumping();
    void setState(State s);
};
