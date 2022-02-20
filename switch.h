#pragma once
#include <vector>

class Switch
{
    public:
    HBITMAP hbm;
    HBITMAP hbmMask;
    int x_pos;
    int y_pos;
    int width;
    int height;
    bool test = false;
    bool wasDown=false;
    bool wasUp=true;
    bool onlyDownSwitch = true;
    bool onlyUpSwitch = true;
    std::vector<Block*> blocks;

    Switch(int x, int y, bool down, bool up)
    {
        onlyDownSwitch = down;
        onlyUpSwitch=up;
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Switches\\switchBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Switches\\switchWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 1;
        height = bitmap.bmHeight / 1;
        x_pos = x;
        y_pos = y;
    }

    void addBlock(Block* block)
    {
        blocks.push_back(block);
    }

    void update(HDC hdc)
    {
        for(auto item:blocks)
        {
            //item->update(hdc);
        }
    }

    bool isPlayerOnSwitch(int x, int y, int w, int h)
    {
         if((x+3>x_pos+7&&x+3<x_pos+width-7&&y+height>y_pos+2&&y+height<y_pos+20) ||
            (x+14>x_pos+7&&x+14<x_pos+width-7&&y+h>y_pos+2&&y+h<y_pos+20) ||
            (x+26>x_pos+7&&x+26<x_pos+width-7&&y+h>y_pos+2&&y+h<y_pos+20)
            )
           {
               return true;
           }
           else
           {
               return false;
           }
    }

    void switchDown()
    {
        if(!wasUp) return;
        wasUp = false;
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Switches\\switchDownBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Switches\\switchDownWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 1;
        height = bitmap.bmHeight / 1;
        for(auto& item: blocks){
            if(onlyUpSwitch){
                item->dx=item->initdx;
                item->dy=item->initdy;
            }
            else{
                item->dx=-item->initdx;
                item->dy=-item->initdy;
            }
        }
        wasDown = true;
    }

    void switchUp()
    {
        if(!wasDown) return;
        wasDown = false;
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Switches\\switchBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Switches\\switchWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BITMAP bitmap;
        GetObject(hbm, sizeof(BITMAP), &bitmap);
        width = bitmap.bmWidth / 1;
        height = bitmap.bmHeight / 1;
        for(auto& item: blocks){
            if(onlyDownSwitch){
                item->dx=-item->initdx;
                item->dy=-item->initdy;
            }
            else{
                item->dx=item->initdx;
                item->dy=item->initdy;
            }
        }
        wasUp = true;
    }
};
