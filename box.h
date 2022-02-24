#pragma once
#include <windows.h>
#include <vector>
#include "player.h"

class Box{
public:
    HBITMAP hbm;
    HBITMAP hbmMask;
    int x_pos;
    int y_pos;
    int width;
    int height;
    int gravity=8;

    Box(int x, int y)
    {
        x_pos = x;
        y_pos = y;

        hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\boxBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\boxWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width=bitmap.bmWidth/1;
        height=bitmap.bmHeight/1;
    }
    Box(){}

    void update(HDC hdc, Player* boy, Player* girl){
        for(int i=0; i<gravity/3; i++)
        {
            COLORREF colorLeft = GetPixel(hdc, x_pos+6, y_pos+height);
            COLORREF colorRight = GetPixel(hdc, x_pos+width/2, y_pos+height);
            COLORREF colorUnder = GetPixel(hdc, x_pos+width-6, y_pos+height);

            if(colorLeft!=FLOOR && colorRight!=FLOOR && colorUnder!=FLOOR)
            {
                y_pos++;
            }
        }
        // check if pushed
        if((boy->x_pos<=x_pos+width&& boy->x_pos>x_pos+width-15 && boy->y_pos+boy->height-5<=y_pos+height && boy->y_pos>y_pos-25)){
            x_pos--;
        }
        if((boy->x_pos+boy->width>=x_pos && boy->x_pos+boy->width<x_pos+15 && boy->y_pos+boy->height-5<=y_pos+height && boy->y_pos>y_pos-25)){
            x_pos++;
        }
        if((girl->x_pos<=x_pos+width&& girl->x_pos>x_pos+width-15 && girl->y_pos+girl->height-5<=y_pos+height && girl->y_pos>y_pos-25)){
            x_pos--;
        }
        if((girl->x_pos+girl->width>=x_pos && girl->x_pos+girl->width<x_pos+15 && girl->y_pos+girl->height-5<=y_pos+height && girl->y_pos>y_pos-25)){
            x_pos++;
        }
    }
};

