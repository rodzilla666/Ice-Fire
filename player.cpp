#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int x, int y, PlayerType t){
    x_pos=x;
    y_pos=y;
    type=t;
    setState(standing_right);
}

Player::Player(){
    setState(standing_right);
    x_pos=400;
    y_pos=250;
    type=red;
}

bool Player::isJumping(){
    return gravity==false;
}

void Player::update(HDC hdc){

    if(gravityEnabled)
    {
        for(int i=0; i<gravity; i++)
        {
            COLORREF colorLeft = GetPixel(hdc, x_pos+width/4, y_pos+height);
            COLORREF colorRight = GetPixel(hdc, x_pos+2*(width/4), y_pos+height);
            COLORREF colorUnder = GetPixel(hdc, x_pos+3*(width/4), y_pos+height);

            if(colorLeft!=FLOOR && colorRight!=FLOOR && colorUnder!=FLOOR)
            {
                y_pos++;
            }
        }
    }
    else
    {
        for(int i=0; i<8; i++)
        {
            COLORREF colorLeft = GetPixel(hdc, x_pos+width/4, y_pos);
            COLORREF colorRight = GetPixel(hdc, x_pos+2*(width/4), y_pos);
            COLORREF colorAbove = GetPixel(hdc, x_pos+3*(width/4), y_pos);

            if(colorLeft!=FLOOR && colorRight!=FLOOR && colorAbove!=FLOOR)
            {
                y_pos--;
            }
        }
        jumping++;
        if(jumping==10)
        {
            jumping=0;
            if(lastState==running_right)
                setState(standing_right);
            else
                setState(standing_left);
            gravityEnabled=true;
        }
    }

    if(state==running_right || state==standing_right || state==jumping_right)
    {
        x_animation++;
        if(x_animation==10)
        {
            x_animation=0;
        }
    }
    else if(state==running_left || jumping_left || standing_left)
    {
        x_animation--;
        if(x_animation<0)
        {
            x_animation=9;
        }
    }
}

void Player::moveLeft(HDC hdc){
    setState(running_left);
    COLORREF colorNearFeet = GetPixel(hdc, x_pos, y_pos+5);
    COLORREF colorNearHead = GetPixel(hdc, x_pos, y_pos+height-5);
    if(colorNearHead!=WALL && colorNearFeet!=WALL && colorNearHead!=DARKWALL && colorNearFeet!=DARKWALL)
    {
        x_pos-=dx;
    }
    lastState=running_left;
}

void Player::moveRight(HDC hdc){
    setState(running_right);
    COLORREF colorNearFeet = GetPixel(hdc, x_pos+width, y_pos+5);
    COLORREF colorNearHead = GetPixel(hdc, x_pos+width, y_pos+height-5);
    if(colorNearHead!=WALL && colorNearFeet!=WALL && colorNearHead!=DARKWALL && colorNearFeet!=DARKWALL)
    {
        x_pos+=dx;
    }
    lastState=running_right;
}

void Player::setState(State s){
    state=s;
    if(state==standing_right)
    {
        hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_standing_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_standing_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else if(state==standing_left)
    {
        hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_standing_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_standing_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else if(state==jumping_right)
    {
        hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_jumping_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_jumping_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else if(state==jumping_left)
    {
        hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_jumping_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_jumping_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else if(state==running_right)
    {
        state=running_right;
        hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_running_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_running_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
    else if(state==running_left)
    {
        state=running_left;
        hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_running_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\boy_running_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }

    BITMAP bitmap;
    GetObject(hbm, sizeof(BITMAP), &bitmap);
    width=bitmap.bmWidth/10;
    height=bitmap.bmHeight/1;
}

void Player::jump(HDC hdc){
    COLORREF colorLeft = GetPixel(hdc, x_pos+width/4, y_pos+height);
    COLORREF colorRight = GetPixel(hdc, x_pos+2*(width/4), y_pos+height);
    COLORREF colorUnder = GetPixel(hdc, x_pos+3*(width/4), y_pos+height);

    if(colorLeft==FLOOR || colorRight==FLOOR || colorUnder==FLOOR)
    {
        if(lastState==running_right)
            setState(jumping_right);
        else
            setState(jumping_left);
        gravityEnabled=false;
    }
}
