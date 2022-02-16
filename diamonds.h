#pragma once
#include "player.h"
#include <iostream>

class Diamonds{
    public:
    HBITMAP hbm;
    HBITMAP hbmMask;

    int x_pos;
    int y_pos;
    int width;
    int height;
    PlayerType type;
    bool collected=false;

    Diamonds(int x, int y, PlayerType t){
        x_pos=x;
        y_pos=y;
        type=t;
        if (type == blue)
        {
            hbm = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondBlueBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondBlueWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

            BITMAP bitmap;
            GetObject(hbm, sizeof(BITMAP), &bitmap);
            width = bitmap.bmWidth / 1;
            height = bitmap.bmHeight / 1;
        }
        else if(type==red)
        {
            hbm = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondRedBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondRedWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

            BITMAP bitmap;
            GetObject(hbm, sizeof(BITMAP), &bitmap);
            width = bitmap.bmWidth / 1;
            height = bitmap.bmHeight / 1;
        }
    }

    Diamonds(){}
    void update(HDC hdc){}

    bool isCollected()
    {
        return collected;
    }

    void collect()
    {
        collected=true;
    }

    bool isPlayerOnDiamond(int x, int y, int w, int h, PlayerType t)
    {
        if(isCollected()) return false;
       // std::cout<<x<<" "<<y<<" "<< x_pos<<" "<< y_pos<<" "<< width<<" " << height<<std::endl;
        if((x>x_pos&&x<x_pos+width&&y>y_pos&&y<y_pos+width) ||
           (x+w>x_pos&&x+w<x_pos+width&&y>y_pos&&y<y_pos+width) ||
           (x>x_pos&&x<x_pos+width&&y+h>y_pos&&y+h<y_pos+width) ||
           (x+w>x_pos&&x+w<x_pos+width&&y+h>y_pos&&y+h<y_pos+width) ||
           (x>x_pos&&x<x_pos+width&&y+h/2>y_pos&&y+h/2<y_pos+width) ||
           (x+w>x_pos&&x+w<x_pos+width&&y+h/2>y_pos&&y+h/2<y_pos+width) ||
           (x>x_pos&&x<x_pos+width&&y+(2*h)/3>y_pos&&y+(2*h)/3<y_pos+width) ||
           (x+w>x_pos&&x+w<x_pos+width&&y+(2*h)/3>y_pos&&y+(2*h)/3<y_pos+width)||
           (x>x_pos&&x<x_pos+width&&y+(1*h)/3>y_pos&&y+(1*h)/3<y_pos+width) ||
           (x+w>x_pos&&x+w<x_pos+width&&y+(1*h)/3>y_pos&&y+(1*h)/3<y_pos+width ) ||
           (x+w/2>x_pos&&x+w/2<x_pos+width&&y>y_pos&&y<y_pos+width) ||
           (x+w/2>x_pos&&x+w/2<x_pos+width&&y+h>y_pos&&y+h<y_pos+width)
           )
        {
            if(t==type)
                return true;
            else
                return false;
        }
        else
        {
            return false;
        }
    }
};
