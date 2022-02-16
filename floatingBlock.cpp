#include "floatingBlock.h"
#include <iostream>
using namespace std;

Block::Block(int x, int y, int xmi, int xma, int ymi, int yma, int dxx, int dyy, BlockType t) {
    x_pos = x;
    y_pos = y;
    xMax = xma;
    xMin = xmi;
    type = t;
    dx = dxx;
    dy = dyy;
    yMax = yma;
    yMin = ymi;
    if (type == good)
    {
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 1;
        height = bitmap.bmHeight / 1;
    }
    else if (type == goodBig)
    {
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockBigBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockBigWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 1;
        height = bitmap.bmHeight / 1;
    }
    else
    {
        // ucitat bad block za type == bad
        //hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\BadBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        //hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\BadBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 1;
        height = bitmap.bmHeight / 1;
    }
}

Block::Block() {
    // setState(moving_right);
    x_pos = 400;
    y_pos = 250;
    type = good;
    hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    BITMAP bitmap;
    GetObject(hbm, sizeof(BITMAP), &bitmap);
    width = bitmap.bmWidth / 1;
    height = bitmap.bmHeight / 1;
}


void Block::update(HDC hdc, Player* boy, Player* girl)
{
    x_pos += dx;
    if(boy->standingOnWhiteBlock &&
           ((boy->x_pos+boy->width/2-15>x_pos && boy->x_pos+boy->width/2-15<x_pos+width && boy->y_pos+boy->height>y_pos-3 && boy->y_pos+boy->height < y_pos+3) ||
            (boy->x_pos+boy->width/2+15>x_pos && boy->x_pos+boy->width/2+15<x_pos+width && boy->y_pos+boy->height>y_pos-3 && boy->y_pos+boy->height < y_pos+3)))
    {
        boy->x_pos+=dx;
    }

    if(girl->standingOnWhiteBlock &&
           ((girl->x_pos+girl->width/2-15>x_pos && girl->x_pos+girl->width/2-15<x_pos+width && girl->y_pos+girl->height>y_pos-3 && girl->y_pos+girl->height < y_pos+3) ||
            (girl->x_pos+girl->width/2+15>x_pos && girl->x_pos+girl->width/2+15<x_pos+width && girl->y_pos+girl->height>y_pos-3 && girl->y_pos+girl->height < y_pos+3)))
    {
        girl->x_pos+=dx;
    }
    if (x_pos >= xMax || x_pos<=xMin)
    {
        dx = -dx;
    }

    y_pos += dy;
    if(boy->standingOnWhiteBlock &&
           ((boy->x_pos+boy->width/2-15>x_pos && boy->x_pos+boy->width/2-15<x_pos+width && boy->y_pos+boy->height>y_pos-3 && boy->y_pos+boy->height < y_pos+3) ||
            (boy->x_pos+boy->width/2+15>x_pos && boy->x_pos+boy->width/2+15<x_pos+width && boy->y_pos+boy->height>y_pos-3 && boy->y_pos+boy->height < y_pos+3)))
    {
        boy->y_pos+=dy;
    }
    if(girl->standingOnWhiteBlock &&
           ((girl->x_pos+girl->width/2-15>x_pos && girl->x_pos+girl->width/2-15<x_pos+width && girl->y_pos+girl->height>y_pos-3 && girl->y_pos+girl->height < y_pos+3) ||
            (girl->x_pos+girl->width/2+15>x_pos && girl->x_pos+girl->width/2+15<x_pos+width && girl->y_pos+girl->height>y_pos-3 && girl->y_pos+girl->height < y_pos+3)))
    {
        girl->y_pos+=dy;
    }
    if (y_pos >= yMax || y_pos <= yMin)
    {
        dy = -dy;
    }
}


