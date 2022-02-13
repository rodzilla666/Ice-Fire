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
        hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\GoodBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\GoodBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

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
    hbm = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\GoodBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    hbmMask = (HBITMAP)LoadImage(NULL, L"Resources\\Sprites\\GoodBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    BITMAP bitmap;
    GetObject(hbm, sizeof(BITMAP), &bitmap);
    width = bitmap.bmWidth / 1;
    height = bitmap.bmHeight / 1;
}


void Block::update(HDC hdc)
{
    x_pos += dx;
    if (x_pos >= xMax || x_pos<=xMin)
    {
        dx = -dx;
    }
    y_pos += dy;
    if (y_pos >= yMax || y_pos <= yMin)
    {
        dy = -dy;
    }
}


