#include "player.h"
#include <iostream>
using namespace std;

Player::Player(int w, int h, int x, int y, PlayerType t){
    x_pos=x;
    y_pos=y;
    width=w;
    height=h;
    type=t;
}

Player::Player(){
}

void Player::update(HDC hdc){
    COLORREF colorUnderPlayer = GetPixel(hdc, x_pos+220, y_pos+270);
    //cout<<(int)GetRValue(colorUnderPlayer)<<" "<< (int)GetGValue(colorUnderPlayer) << " " <<
    //        (int)GetBValue(colorUnderPlayer)<<" " << x_pos << " " << y_pos<< endl;
    //cout<<colorUnderPlayer<<endl;
    cout<<height<<" " << width<<endl;
    if(colorUnderPlayer!=0 && gravityEnabled)
    {
        y_pos+=gravity;
    }

}

void Player::moveLeft(HDC hdc){
    COLORREF colorUnderPlayer = GetPixel(hdc, x_pos+140, y_pos+150);
    if(colorUnderPlayer!=0)    x_pos-=dx;
}

void Player::moveRight(HDC hdc){
    COLORREF colorUnderPlayer = GetPixel(hdc, x_pos+300, y_pos+150);
    if(colorUnderPlayer!=0)    x_pos+=dx;
}

void Player::jump(){

}
