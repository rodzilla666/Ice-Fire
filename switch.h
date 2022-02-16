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
    std::vector<Block*> blocks;
    Switch(int x, int y)
    {
        hbm = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMask = (HBITMAP)LoadImage(NULL, "Resources\\Sprites\\GoodBlockWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
            item->update(hdc);
        }
    }
};
