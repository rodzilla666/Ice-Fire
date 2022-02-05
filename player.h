#pragma once
#include <windows.h>
enum State { standing, running_left, running_right, jumping };
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
    bool gravityEnabled=false;
    int gravity=8;
    PlayerType type;
    State state=standing;

    Player(int w, int h, int x, int y, PlayerType t);
    Player();
    void update(HDC hdc); // animation, gravity
    void moveLeft(HDC hdc);
    void moveRight(HDC hdc);
    void jump();
};
