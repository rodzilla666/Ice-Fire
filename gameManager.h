
#pragma once
#include "player.h"
#include "floatingBlock.h"
#include "switch.h"
#include "diamonds.h"
#include "numbers.h"
#include "box.h"
#include <chrono>
#include <thread>
#include <future>
#include <fstream>
#include <string>
enum GameState { Level, MainMenu, GameOver, LevelPassed, Idle };

#define KEYDOWN(vk_code) ((GetKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_A 0x41
#define KEY_D 0x44
#define KEY_S 0x53
#define KEY_W 0x57

#define PLAYBUTTON 801
#define LOGINBUTTON 802
#define SETTINGSBUTTON 803
#define LEADERBOARDBUTTON 804
#define EXITBUTTON 805
#define PLAYAGAINBUTTON 807
#define MAINMENUBUTTON 808

struct Object {
	int width;
	int height;
	int x = 5;
	int y = 5;
}background;

class GameManager {
public:
    GameState gameState = Level;
    Player* boy = nullptr;
    Player* girl = nullptr;
    std::vector<Block*> goodBlocks;
    std::vector<Switch*> switches;
    std::vector<Diamonds*> diamonds;
    std::vector<Box*> boxes;

    Numbers* numbersBlue=nullptr;
    Numbers* numbersRed=nullptr;

    unsigned int numOfSeconds = 0;

    HBITMAP hbmBackground = NULL;
    HWND hwnd = NULL;

    HBITMAP playButtonImage = NULL;
    HBITMAP loginButtonImage = NULL;
    HBITMAP settingsButtonImage = NULL;
    HBITMAP leaderboardButtonImage = NULL;
    HBITMAP exitButtonImage = NULL;
    HBITMAP playAgainButtonImage = NULL;
    HBITMAP mainMenuButtonImage = NULL;

    HWND hwndGameOverWindow = NULL;
    HWND playButton = NULL;
    HWND loginButton = NULL;
    HWND settingsButton = NULL;
    HWND leaderboardButton = NULL;
    HWND exitButton = NULL;
    HWND playAgainButton = NULL;
    HWND mainMenuButton = NULL;

    HBITMAP hbmblue;
    HBITMAP hbmMaskblue;
    HBITMAP hbmred;
    HBITMAP hbmMaskred;
    HBITMAP hbmClock;
    HBITMAP hbmMaskClock;
    HBITMAP hbmColon;
    HBITMAP hbmMaskColon;

    bool liftPlayer = false;
    bool playingSound = false;

    int delayTimer=0;
    int delayFrames=100;

    GameManager(HWND h) : hwnd{ h } {
        PlaySound("gameSong.wav", NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        Initialize();
        numbersBlue=new Numbers(780, 25);
        numbersRed=new Numbers(865, 25);
    }


    ~GameManager() {
        delete boy;
        delete girl;
        delete numbersBlue;
        delete numbersRed;

        for (auto& item : goodBlocks)
        {
            delete item;
        }

        for (auto& item : diamonds)
        {
            delete item;
        }
    }

    void addTime(){
        if(gameState==Level)
        {
            numOfSeconds++;
        }
    }

    void Initialize() {

        // za main menu
        hbmBackground = (HBITMAP)LoadImage(NULL, "Resources\\Menus\\StartMenu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BITMAP bitmap;
        GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
        background.width = bitmap.bmWidth;
        background.height = bitmap.bmHeight;

        playButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\PlayButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        playButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 361, 179, 275, 70, hwnd, (HMENU)PLAYBUTTON, NULL, NULL);
        SendMessageW(playButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)playButtonImage);

        loginButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\LoginButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        loginButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 361, 251, 275, 70, hwnd, (HMENU)LOGINBUTTON, NULL, NULL);
        SendMessageW(loginButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)loginButtonImage);

        settingsButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\SettingsButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        settingsButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 361, 327, 275, 70, hwnd, (HMENU)SETTINGSBUTTON, NULL, NULL);
        SendMessageW(settingsButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)settingsButtonImage);

        leaderboardButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\LeaderboardButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        leaderboardButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 361, 403, 275, 70, hwnd, (HMENU)LEADERBOARDBUTTON, NULL, NULL);
        SendMessageW(leaderboardButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)leaderboardButtonImage);

        exitButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\ExitButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        exitButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 361, 479, 275, 70, hwnd, (HMENU)EXITBUTTON, NULL, NULL);
        SendMessageW(exitButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)exitButtonImage);

        gameState = MainMenu;

        hbmblue = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondBlueBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMaskblue = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondBlueWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmred = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondRedBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMaskred = (HBITMAP)LoadImage(NULL, "Resources\\Diamonds\\DiamondRedWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        hbmClock = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Numbers\\watchBlack2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMaskClock = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Numbers\\watchWhite2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

        hbmColon = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Numbers\\colonBlack.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        hbmMaskColon = (HBITMAP)LoadImage(NULL, "Resources\\UI\\Numbers\\colonWhite.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    }

    void CheckInput(HDC hdc)
    {
        if (!KEYDOWN(KEY_A) && !KEYDOWN(KEY_D) && !KEYDOWN(KEY_W))
        {
            if (!boy->isJumping() && boy->state != dead_right)
            {
                if (boy->lastState == running_right)
                    boy->setState(standing_right);
                else
                    boy->setState(standing_left);
            }
        }
        else if (KEYDOWN(KEY_A))
        {
            boy->moveLeft(hdc);
        }
        else if (KEYDOWN(KEY_D))
        {
            boy->moveRight(hdc);
        }
        if (KEYDOWN(KEY_W))
        {
            if(!playingSound)
            {
                mciSendString("open jump.wav type waveaudio alias jump", NULL, 0, NULL);
                mciSendString("play jump notify", NULL, NULL, hwnd);
                playingSound = true;
            }
            boy->jump(hdc);
        }
        if (KEYDOWN(KEY_S))
        {
            boy->setState(standing_right);
        }

////////////////////////////////////////////////////////////////
        if (KEYDOWN(VK_SPACE))
        {
           // goodBlocks[1]->dy = -2;
           // goodBlocks[2]->dy = -2;
          //  goodBlocks[3]->dy = -2;
        }
        if (KEYDOWN(VK_F1))
        {

            if(!playingSound)
            {
                mciSendString("open lift.wav type waveaudio alias lift", NULL, 0, NULL);
                mciSendString("play lift notify", NULL, NULL, hwnd);
                playingSound = true;
            }
         //   goodBlocks[1]->dy = 2;
        //    goodBlocks[2]->dy = 2;
         //   goodBlocks[3]->dy = 2;
        }
        if (KEYDOWN(VK_F2))
        {
          //  goodBlocks[4]->dx = 1;
        }
        if (KEYDOWN(VK_F3))
        {
           // goodBlocks[4]->dx = -1;
        }
        if (KEYDOWN(VK_F4))
        {
           // goodBlocks[5]->dy = 1;
        }
        if (KEYDOWN(VK_F5))
        {
           // goodBlocks[5]->dy = -1;
           // liftPlayer = true;
        }
/////////////////////////////////////////////////////////////////////////

        if (!KEYDOWN(VK_UP) && !KEYDOWN(VK_LEFT) && !KEYDOWN(VK_RIGHT))
        {
            if (!girl->isJumping() && girl->state != dead_right)
            {
                if (girl->lastState == running_right)
                    girl->setState(standing_right);
                else
                    girl->setState(standing_left);
            }
        }
        else if (KEYDOWN(VK_LEFT))
        {
            girl->moveLeft(hdc);
        }
        else if (KEYDOWN(VK_RIGHT))
        {
            girl->moveRight(hdc);
        }
        if (KEYDOWN(VK_UP))
        {
            if(!playingSound)
            {
                mciSendString("open jump.wav type waveaudio alias jump", NULL, 0, NULL);
                mciSendString("play jump notify", NULL, NULL, hwnd);
                playingSound = true;
            }
            girl->jump(hdc);
        }

        if (KEYDOWN(VK_DOWN))
        {
            girl->setState(standing_right);
        }
    }

    void Update()
    {
        HDC hdc = GetDC(hwnd);
        ////////////////////////////////////////////////////////


        if (gameState==Level && (boy->state == dead_left || boy->state == dead_right || girl->state == dead_left || girl->state == dead_right))
        {
            delayTimer++;
            // play "player died" sound
        }
        if(delayTimer>delayFrames)
        {
            gameState = GameOver;
            delayTimer = 0;
        }
        else if(delayTimer>0)
        {
            delayTimer++;
        }
        ///////////////////////////////////////////////////////////

        if(gameState==Level)
        {
            CheckInput(hdc);
            boy->update(hdc);
            girl->update(hdc);

            for (auto item : goodBlocks)
            {
                item->update(hdc, boy, girl);
            }

            for (auto item : boxes)
            {
                item->update(hdc, boy, girl);
            }

            for (auto item : switches)
            {
                if(item->isPlayerOnSwitch(boy->x_pos, boy->y_pos, boy->width, boy->height) ||
                   item->isPlayerOnSwitch(girl->x_pos, girl->y_pos, girl->width, girl->height))
                {
                    item->switchDown();
                }
                else
                {
                    item->switchUp();
                }
                for(auto item1 : item->blocks)
                {
                    item1->update(hdc, boy, girl);
                }

            }

            for(auto item: diamonds)
            {
                if(item->isPlayerOnDiamond(boy->x_pos, boy->y_pos, boy->width, boy->height,boy->type))
                {
                    item->collect();
                    boy->addDiamond();
                }
                else if(item->isPlayerOnDiamond(girl->x_pos, girl->y_pos, girl->width, girl->height, girl->type))
                {
                    item->collect();
                    girl->addDiamond();
                }
            }

        }
        if (gameState != Idle)
        {
            RECT clientRect;
            GetClientRect(hwnd, &clientRect);
            Draw(hdc, &clientRect);
        }

        ReleaseDC(hwnd, hdc);
    }

    void Draw(HDC hdc, RECT* rect)
    {
        HDC hdcBuffer = CreateCompatibleDC(hdc);
        HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect->right, rect->bottom);
        HBITMAP hbmOldBuffer = (HBITMAP)SelectObject(hdcBuffer, hbmBuffer);

        HDC hdcMem = CreateCompatibleDC(hdc);
        HBITMAP hbmOld1 = (HBITMAP)SelectObject(hdcMem, hbmBackground);
        BitBlt(hdcBuffer, background.x, background.y, background.width, background.height, hdcMem, 0, 0, SRCCOPY);

        HBITMAP hbmOld = 0;
        if (gameState==Level || gameState == GameOver)
        {
            SelectObject(hdcMem, boy->hbmMask);
            BitBlt(hdcBuffer, boy->x_pos, boy->y_pos, boy->width, boy->height, hdcMem, boy->x_animation * boy->width, boy->y_animation * boy->height, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, boy->hbm);
            BitBlt(hdcBuffer, boy->x_pos, boy->y_pos, boy->width, boy->height, hdcMem, boy->x_animation * boy->width, boy->y_animation * boy->height, SRCPAINT);

            SelectObject(hdcMem, girl->hbmMask);
            BitBlt(hdcBuffer, girl->x_pos, girl->y_pos, girl->width, girl->height, hdcMem, girl->x_animation * girl->width, girl->y_animation * girl->height, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, girl->hbm);
            BitBlt(hdcBuffer, girl->x_pos, girl->y_pos, girl->width, girl->height, hdcMem, girl->x_animation * girl->width, girl->y_animation * girl->height, SRCPAINT);

            for (auto item : goodBlocks)
            {
                SelectObject(hdcMem, item->hbmMask);
                BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCAND);

                hbmOld = (HBITMAP)SelectObject(hdcMem, item->hbm);
                BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCPAINT);
            }
            // crtaj dijamante
            for (auto item : diamonds)
            {
                if(item->isCollected()==false)
                {
                    SelectObject(hdcMem, item->hbmMask);
                    BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCAND);

                    hbmOld = (HBITMAP)SelectObject(hdcMem, item->hbm);
                    BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCPAINT);
                }
            }
            // crtaj kutije
            for (auto item : boxes)
            {
                SelectObject(hdcMem, item->hbmMask);
                BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCAND);

                hbmOld = (HBITMAP)SelectObject(hdcMem, item->hbm);
                BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCPAINT);
            }

            // diamonds collected
            SelectObject(hdcMem, hbmMaskblue);
            BitBlt(hdcBuffer, 740, 30, 29, 30, hdcMem, 0, 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, hbmblue);
            BitBlt(hdcBuffer, 740, 30, 29, 30, hdcMem, 0, 0, SRCPAINT);

            SelectObject(hdcMem, hbmMaskred);
            BitBlt(hdcBuffer, 825, 30, 29, 30, hdcMem, 0, 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, hbmred);
            BitBlt(hdcBuffer, 825, 30, 29, 30, hdcMem, 0, 0, SRCPAINT);

            // numbers
            //std::cout<<boy->diamondsCollected<<std::endl;
            SelectObject(hdcMem, numbersBlue->hbmMask);
            BitBlt(hdcBuffer, numbersBlue->x_pos, numbersBlue->y_pos, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * boy->diamondsCollected, 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, numbersBlue->hbm);
            BitBlt(hdcBuffer, numbersBlue->x_pos, numbersBlue->y_pos, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * boy->diamondsCollected, 0, SRCPAINT);

            SelectObject(hdcMem, numbersRed->hbmMask);
            BitBlt(hdcBuffer, numbersRed->x_pos, numbersRed->y_pos, numbersRed->width, numbersRed->height, hdcMem, numbersRed->width * girl->diamondsCollected, 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, numbersRed->hbm);
            BitBlt(hdcBuffer, numbersRed->x_pos, numbersRed->y_pos, numbersRed->width, numbersRed->height, hdcMem, numbersRed->width * girl->diamondsCollected, 0, SRCPAINT);

            // Timer
            SelectObject(hdcMem, hbmMaskClock);
            BitBlt(hdcBuffer, 425, 20, 40, 40, hdcMem, 0, 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, hbmClock);
            BitBlt(hdcBuffer, 425, 20, 40, 40, hdcMem, 0, 0, SRCPAINT);

            // numbers for the timer

            // minutes
            SelectObject(hdcMem, numbersBlue->hbmMask);
            BitBlt(hdcBuffer, 465, 25, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * (numOfSeconds/60), 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, numbersBlue->hbm);
            BitBlt(hdcBuffer, 465, 25, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * (numOfSeconds/60), 0, SRCPAINT);

            // colon
            SelectObject(hdcMem, hbmMaskColon);
            BitBlt(hdcBuffer, 487, 25, 9, 40, hdcMem, 0, 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, hbmColon);
            BitBlt(hdcBuffer, 487, 25, 9, 40, hdcMem, 0, 0, SRCPAINT);

            // seconds 1
            SelectObject(hdcMem, numbersBlue->hbmMask);
            BitBlt(hdcBuffer, 495, 25, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * ((numOfSeconds%60)/10), 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, numbersBlue->hbm);
            BitBlt(hdcBuffer, 495, 25, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * ((numOfSeconds%60)/10), 0, SRCPAINT);
            // seconds 2
            SelectObject(hdcMem, numbersBlue->hbmMask);
            BitBlt(hdcBuffer, 525, 25, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * ((numOfSeconds%60)%10), 0, SRCAND);

            hbmOld = (HBITMAP)SelectObject(hdcMem, numbersBlue->hbm);
            BitBlt(hdcBuffer, 525, 25, numbersBlue->width, numbersBlue->height, hdcMem, numbersBlue->width * ((numOfSeconds%60)%10), 0, SRCPAINT);


            for (auto item : switches)
            {
                SelectObject(hdcMem, item->hbmMask);
                BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCAND);

                hbmOld = (HBITMAP)SelectObject(hdcMem, item->hbm);
                BitBlt(hdcBuffer, item->x_pos, item->y_pos, item->width, item->height, hdcMem, 0, 0, SRCPAINT);

                    for (auto item1 : item->blocks)
                    {
                        SelectObject(hdcMem, item1->hbmMask);
                        BitBlt(hdcBuffer, item1->x_pos, item1->y_pos, item1->width, item1->height, hdcMem, 0, 0, SRCAND);

                        hbmOld = (HBITMAP)SelectObject(hdcMem, item1->hbm);
                        BitBlt(hdcBuffer, item1->x_pos, item1->y_pos, item1->width, item1->height, hdcMem, 0, 0, SRCPAINT);
                    }
            }

        }

        if (gameState == GameOver)
        {
            gameState = Idle;
            hbmBackground = (HBITMAP)LoadImage(NULL, "Resources\\Menus\\GameOver.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
            HBITMAP hbmOld1 = (HBITMAP)SelectObject(hdcMem, hbmBackground);
            BitBlt(hdcBuffer, 200, 150, background.width, background.height, hdcMem, 0, 0, SRCCOPY);
            ShowGameOverScreen();
        }
        SelectObject(hdc, hbmOld1);

        BitBlt(hdc, 0, 0, rect->right, rect->bottom, hdcBuffer, 0, 0, SRCCOPY);

        SelectObject(hdcMem, hbmOld);
        DeleteObject(hdcMem);
        DeleteObject(hbmBuffer);

        SelectObject(hdcBuffer, hbmOldBuffer);
        DeleteObject(hdcBuffer);
        DeleteObject(hbmOldBuffer);
    }

    void ShowGameOverScreen()
    {
        playAgainButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\PlayAgainButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        playAgainButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 360, 257, 275, 70, hwnd, (HMENU)PLAYAGAINBUTTON, NULL, NULL);
        SendMessageW(playAgainButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)playAgainButtonImage);

        mainMenuButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\MainMenuButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
        mainMenuButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 360, 337, 275, 70, hwnd, (HMENU)MAINMENUBUTTON, NULL, NULL);
        SendMessageW(mainMenuButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)mainMenuButtonImage);
    }

    void InitializeLevel()
    {
        numOfSeconds=0;
        gameState = Level;

        for (auto& item : goodBlocks)
        {
            delete item;
        }
        goodBlocks.clear();

        for (auto& item : diamonds)
        {
            delete item;
        }
        diamonds.clear();

        for (auto& item : boxes)
        {
            delete item;
        }
        boxes.clear();

        for (auto& item : switches)
        {
            for(auto& item1: item->blocks){
                if(!(item->onlyUpSwitch))
                    delete item1;
            }
            (item->blocks).clear();
            delete item;
        }
        switches.clear();

        delete boy;
        delete girl;

        // pocetak ucitavanja levela
        std::ifstream input("Resources\\Levels\\gameInfo.txt");
        int levelNum;
        input>>levelNum;
        input.close();

        std::string level = "Resources\\Levels\\Level"+std::to_string(levelNum)+".bmp";
        hbmBackground = (HBITMAP)LoadImage(NULL, level.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BITMAP bitmap;
        GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
        background.width = bitmap.bmWidth;
        background.height = bitmap.bmHeight;

        level = "Resources\\Levels\\level"+std::to_string(levelNum)+".txt";
        input.open(level.c_str());

        int numOfPlayers;
        input>>numOfPlayers;
        int x,y;
        int t;
        for(int i=0; i<numOfPlayers; i++){
            input>>x>>y>>t;
            if(t==1)
                boy=new Player(x,y,blue);
            else
                girl=new Player(x,y,red);
        }

        int numOfIndependentBlocks;
        input>>numOfIndependentBlocks;

        int xmi, xma, ymi, yma, dxx, dyy;
        for(int i=0; i<numOfIndependentBlocks; i++){
            input>>x>>y>>xmi>>xma>>ymi>>yma>>dxx>>dyy;
            //std::cout<<x<<" "<<y<<" "<<xmi<< " "<<xma<<" "<<ymi<< " " <<yma<< " "<<dxx<<" "<<dyy<<std::endl;
            goodBlocks.push_back(new Block(x, y, xmi, xma, ymi, yma, dxx, dyy, good, true));
        }

        int numOfSwitches;
        input>>numOfSwitches;
        int down, up;
        for(int i=0; i<numOfSwitches; i++){
            input>>x>>y>>down>>up;
            switches.push_back(new Switch(x, y, down, up));
            int numOfBlocksInSwitch;
            input>>numOfBlocksInSwitch;
            if(!up){
                for(int j=0; j<numOfBlocksInSwitch; j++){
                    input>>x>>y>>xmi>>xma>>ymi>>yma>>dxx>>dyy>>t;
                    if(t==1)
                        switches[i]->addBlock(new Block(x, y, xmi, xma, ymi, yma, dxx, dyy, good, false));
                    else
                        switches[i]->addBlock(new Block(x, y, xmi, xma, ymi, yma, dxx, dyy, goodBig, false));
                }
            }
            else{
                int numOfComplementSwitch;
                input>>numOfComplementSwitch;
                for(int j=0; j<numOfBlocksInSwitch; j++){
                    switches[i]->addBlock(switches[numOfComplementSwitch-1]->blocks[j]);
                }
            }
        }

        int numOfDiamonds;
        input>>numOfDiamonds;
        for(int i=0; i<numOfDiamonds; i++){
            input>>x>>y>>t;
            if(t==1){
                diamonds.push_back(new Diamonds(x, y, blue));
            }
            else{
                diamonds.push_back(new Diamonds(x, y, red));
            }
        }

        int numOfBoxes;
        input>>numOfBoxes;
        for(int i=0; i<numOfBoxes; i++){
            input>>x>>y;
            boxes.push_back(new Box(x, y));
        }

        input.close();
        // kraj ucitavanja levela
    }

    void DestroyMainMenu() {
        DestroyWindow(playButton);
        DestroyWindow(loginButton);
        DestroyWindow(settingsButton);
        DestroyWindow(leaderboardButton);
        DestroyWindow(exitButton);
    }

    void ResetLevelParameters()
    {
        //boy->x_pos = initX;
        boy->x_pos = 30;
        boy->y_pos = 0;
        girl->x_pos = 5;
        girl->y_pos = 0;
        boy->setState(standing_right);
        girl->setState(standing_right);
    }

    void DestroyGameOverMenu() {
        DestroyWindow(playAgainButton);
        DestroyWindow(mainMenuButton);
    }
};
