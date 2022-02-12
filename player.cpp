#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int x, int y, PlayerType t) {
    x_pos = x;
    y_pos = y;
    type = t;
    setState(standing_right);
    if (type == red) 
    {
        states[0].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_standing_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[0].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_standing_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[1].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_standing_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[1].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_standing_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[2].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_jumping_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[2].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_jumping_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[3].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_jumping_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[3].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_jumping_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[4].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_running_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[4].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_running_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[5].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_running_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[5].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_running_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[6].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_dead_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[6].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\girl_dead_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    }
    else
    {
        states[0].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_standing_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[0].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_standing_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[1].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_standing_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[1].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_standing_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[2].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_jumping_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[2].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_jumping_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[3].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_jumping_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[3].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_jumping_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[4].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_running_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[4].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_running_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[5].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_running_left_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[5].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_running_left_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        states[6].hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_dead_right_black.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        states[6].hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\boy_dead_right_white.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }
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
            COLORREF colorLeft = GetPixel(hdc, x_pos+width/2-18, y_pos+height);
            COLORREF colorRight = GetPixel(hdc, x_pos+width/2, y_pos+height);
            COLORREF colorUnder = GetPixel(hdc, x_pos+width/2+15, y_pos+height);

            if(colorLeft!=FLOOR && colorRight!=FLOOR && colorUnder!=FLOOR)
            {
                y_pos++;
            }
            if(colorUnder!=FLOOR)
                cout<<colorUnder<<endl;
            if(type==blue && colorUnder>=7930&&colorUnder<8999)
            {
               // cout<<"LAVA"<<endl;
               setState(dead_right);
            }
            else if(type==red && colorUnder>=16252555&&colorUnder<=16509456)
            {
               setState(dead_right);
            }
        }
    }
    else
    {
        for(int i=0; i<jumpVal[jumping]; i++)
        {
            COLORREF colorLeft = GetPixel(hdc, x_pos+width/4, y_pos);
            COLORREF colorRight = GetPixel(hdc, x_pos+2*(width/4), y_pos);
            COLORREF colorAbove = GetPixel(hdc, x_pos+3*(width/4), y_pos);

            if(colorLeft!=FLOOR && colorRight!=FLOOR && colorAbove!=FLOOR &&
               colorLeft!=WALL && colorRight!=WALL && colorAbove!=WALL)
            {
                y_pos--;
            }
            else
            {
                jumping = 12;
                break;
            }
        }
        jumping++;
        if(jumping==13)
        {
            jumping=0;
            if(lastState==running_right)
                setState(standing_right);
            else
                setState(standing_left);
            gravityEnabled=true;
        }
    }

    if(state==running_right || state==standing_right || state==jumping_right || state==dead_right)
    {
        x_animation++;
        if(x_animation>=10)
        {
            if(state!=dead_right)
                x_animation=0;
            else
                x_animation=9;
        }
    }
    else if(state==running_left || state == jumping_left || state == standing_left)
    {
        x_animation--;
        if(x_animation<0)
        {
            x_animation=9;
        }
    }
}

void Player::moveLeft(HDC hdc){
    if(state==dead_right) return;
    setState(running_left);
    for(int i=0; i<dx; i++)
    {
        COLORREF color1 = GetPixel(hdc, x_pos, y_pos+5);
        COLORREF color2 = GetPixel(hdc, x_pos, y_pos+height/6);
        COLORREF color3 = GetPixel(hdc, x_pos, y_pos+height/3);
        COLORREF color4 = GetPixel(hdc, x_pos, y_pos+height/2);
        COLORREF color5 = GetPixel(hdc, x_pos, y_pos+4*height/6);
        COLORREF color6 = GetPixel(hdc, x_pos, y_pos+5*height/6);
        COLORREF color7 = GetPixel(hdc, x_pos, y_pos+height-5);
            //std::cout << color1 << " " << color2 << " " << color3 << " " << color4 << " " << color5 << " " << color6 << " " << color7 << std::endl;
        if(color1!=WALL && color2!=WALL && color3!=WALL && color4!=WALL && color5!=WALL && color6!=WALL && color7!=WALL && 
           color1!=FLOOR && color2!=FLOOR && color3!=FLOOR && color4!=FLOOR && color5!=FLOOR && color6!=FLOOR && color7!=FLOOR)
        {
            x_pos--;
        }
    }
    lastState=running_left;
}


void Player::moveRight(HDC hdc){
    if(state==dead_right) return;
    setState(running_right);
    for(int i=0; i<dx; i++)
    {
        COLORREF color1 = GetPixel(hdc, x_pos+width-5, y_pos+5);
        COLORREF color2 = GetPixel(hdc, x_pos+width-5, y_pos+height/6);
        COLORREF color3 = GetPixel(hdc, x_pos+width-5, y_pos+height/3);
        COLORREF color4 = GetPixel(hdc, x_pos+width-5, y_pos+height/2);
        COLORREF color5 = GetPixel(hdc, x_pos+width-5, y_pos+4*height/6);
        COLORREF color6 = GetPixel(hdc, x_pos+width-5, y_pos+5*height/6);
        COLORREF color7 = GetPixel(hdc, x_pos+width-5, y_pos+height-5);
        if(color1!=WALL && color2!=WALL && color3!=WALL && color4!=WALL && color5!=WALL && color6!=WALL && color7!=WALL &&
           color1!=FLOOR && color2!=FLOOR && color3!=FLOOR && color4!=FLOOR && color5!=FLOOR && color6!=FLOOR && color7!=FLOOR)
        {
            x_pos++;
        }
    }
    lastState=running_right;
}

void Player::setState(State s){
    state=s;
    hbm = states[state].hbm;
    hbmMask = states[state].hbmMask;

    BITMAP bitmap;
    GetObject(hbm, sizeof(BITMAP), &bitmap);
    width=bitmap.bmWidth/10;
    height=bitmap.bmHeight/1;
}

void Player::jump(HDC hdc){
    if(state==dead_right) return;
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
