
#pragma once
#include "player.h"
#include "floatingBlock.h"
#include <chrono>
#include <thread>
#include <future>
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
	int x;
	int y;
}background;

class GameManager {
public:
    GameState gameState = Level;
    Player* boy = nullptr;
    Player* girl = nullptr;
    std::vector<Block*> goodBlocks;

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

    GameManager(HWND h) : hwnd{ h } {
        Initialize();
    }

    ~GameManager() {
        delete boy;
        delete girl;
        for (auto& item : goodBlocks)
        {
            delete item;
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
            boy->jump(hdc);
        }
        if (KEYDOWN(KEY_S))
        {
            boy->setState(standing_right);
        }


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
        static bool threadMade = false;

        if (gameState==Level && (boy->state == dead_left || boy->state == dead_right || girl->state == dead_left || girl->state == dead_right))
        {
            // play "player died" sound
            threadMade = true;
            std::async(std::launch::async, [&]() {
                std::this_thread::sleep_for(std::chrono::seconds{1});
                gameState = GameOver;
                threadMade = false;
            });
        }

        if(gameState==Level)
        {
            CheckInput(hdc);
            boy->update(hdc);
            girl->update(hdc);
            for (auto item : goodBlocks)
            {
                item->update(hdc);
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
        gameState = Level;
        hbmBackground = (HBITMAP)LoadImage(NULL, "Resources\\Levels\\level1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        BITMAP bitmap;
        GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
        background.width = bitmap.bmWidth;
        background.height = bitmap.bmHeight;

        for (auto& item : goodBlocks)
        {
            delete item;
        }
        goodBlocks.clear();

        delete boy;
        delete girl;

        boy = new Player(100, 50, blue);
        girl = new Player(50, 50, red);

        goodBlocks.push_back(new Block(400, 100, 400, 490, 50, 150, 1, 0, good));
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
