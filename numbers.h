#pragma once
#include <iostream>
class Numbers{
    public:
    int x_pos;
    int y_pos;
    HBITMAP hbm;
    HBITMAP hbmMask;
    int width;
    int height;

    Numbers(int x, int y)
    {
        x_pos=x;
        y_pos=y;
        //std::cout<<"ctor"<<std::endl;
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Numbers\\numbersBlack2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Numbers\\numbersWhite2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 10;
        height = bitmap.bmHeight / 1;
        //std::cout<<x_pos<<" "<<y_pos<<" "<< width<<" "<< height<<std::endl;
    }
    Numbers(){}
};
