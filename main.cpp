#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "player.h"
#include "floatingBlock.h"

using namespace std;

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

void CheckInput(HDC);
void Update(HWND);
void Render(HWND);
void Initalize(HWND);
void InitializeLevel();
void ShowGameOverScreen();

void Update(RECT*);
void Draw(HDC, RECT*);
void ResetLevelParameters(void);

bool mainMenuActive = true;
bool mainMenuRendered = false;
bool mainMenuInitialized = false;
bool gameOverMenuActive = false;
bool gameOverMenuRendered = false;

HBITMAP playButtonImage;
HBITMAP loginButtonImage;
HBITMAP settingsButtonImage;
HBITMAP leaderboardButtonImage;
HBITMAP exitButtonImage;
HBITMAP playAgainButtonImage;
HBITMAP mainMenuButtonImage;

HWND hwndGameOverWindow;
HWND playButton;
HWND loginButton;
HWND settingsButton;
HWND leaderboardButton;
HWND exitButton;
HWND playAgainButton;
HWND mainMenuButton;

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

HBITMAP hbmBackground;

Player boy(100, 50, blue);
Player girl(50, 50, red);
Block goodBlock(400, 100, good);

struct Object{
    int width;
    int height;
    int x;
    int y;
}background;

const int ID_TIMER = 1;

HWND mainHWND;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{

    HWND hwnd;               /* This is the handle for our window */
    HWND hwndSecondWindow;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    if (!RegisterClassEx (&wincl))
        return 0;

    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1016,                 /* The programs width */
           738,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    ShowWindow (hwnd, nCmdShow);

    if(!mainMenuInitialized)
    {
        Initalize(hwnd);
        mainMenuInitialized = true;
    }

    mainHWND = hwnd;

    while (TRUE)
    {
        DWORD vrijeme_pocetak;

        if(PeekMessage(&messages, NULL, 0,0, PM_REMOVE))
        {
            if(messages.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }

        vrijeme_pocetak = GetTickCount();

        if((boy.state == dead_left || boy.state == dead_right || girl.state == dead_left || girl.state == dead_right) && !gameOverMenuActive)
        {
            gameOverMenuActive = true;
            Render(hwnd);
        }

        if(!mainMenuActive && !gameOverMenuActive)
        {
            HDC hdc = GetDC(hwnd);
            CheckInput(hdc);
            ReleaseDC(hwnd, hdc);
            Update(hwnd);
        }
        if((mainMenuActive && !mainMenuRendered) || (!mainMenuActive && !gameOverMenuActive))
        {
            Render(hwnd);
            mainMenuRendered = mainMenuActive;
            gameOverMenuRendered = gameOverMenuActive;
        }

        //cout << GetTickCount() - vrijeme_pocetak << endl;

        /*HDC hdc = GetDC(hwnd);
        CheckInput(hdc);
        ReleaseDC(hwnd, hdc);
        Update(hwnd);
        Render(hwnd);*/

        while(GetTickCount()- vrijeme_pocetak < 20)
        {
            Sleep(5);
        }
    }
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        //SetTimer(hwnd, ID_TIMER, 20000, NULL);
        break;
    case WM_TIMER:
        if(wParam==ID_TIMER)
        {

        }
        break;
    case WM_DESTROY:
        //KillTimer(hwnd, ID_TIMER);
        PostQuitMessage (0);
        break;
        case WM_COMMAND:
        {
            switch(LOWORD(wParam))
            {
                case PLAYBUTTON:
                {
                    std::cout << "PLAY button pressed" << std::endl;
                    InitializeLevel();
                    mainMenuActive = false;
                    mainMenuRendered = false;
                    DestroyWindow(playButton);
                    DestroyWindow(loginButton);
                    DestroyWindow(settingsButton);
                    DestroyWindow(leaderboardButton);
                    DestroyWindow(exitButton);
                }
                break;
                case LOGINBUTTON:
                {
                    std::cout << "LOGIN button pressed" << std::endl;
                }
                break;
                case SETTINGSBUTTON:
                {
                    std::cout << "SETTINGS button pressed" << std::endl;
                }
                break;
                case LEADERBOARDBUTTON:
                {
                    std::cout << "LEADERBOARD button pressed" << std::endl;
                }
                break;
                case EXITBUTTON:
                {
                    std::cout << "EXIT button pressed" << std::endl;
                    PostQuitMessage(0);
                }
                break;
                case PLAYAGAINBUTTON:
                {
                    std::cout << "PLAYAGAIN button pressed" << std::endl;
                    ResetLevelParameters();
                    InitializeLevel();
                    gameOverMenuActive = false;
                    gameOverMenuRendered = false;
                    DestroyWindow(playAgainButton);
                    DestroyWindow(mainMenuButton);
                }
                break;
                case MAINMENUBUTTON:
                {
                    std::cout << "MAINMENU button pressed" << std::endl;
                    ResetLevelParameters();
                    Initalize(mainHWND);
                    mainMenuActive = true;
                    gameOverMenuActive = false;
                    gameOverMenuRendered = false;
                    DestroyWindow(playAgainButton);
                    DestroyWindow(mainMenuButton);
                }
                break;

            }
        }
    default:
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return 0;
}

void Update(RECT* rect)
{

}

void Draw(HDC hdc, RECT* rect)
{
    HDC hdcBuffer = CreateCompatibleDC(hdc);
    HBITMAP hbmBuffer = CreateCompatibleBitmap(hdc, rect->right, rect->bottom);
    HBITMAP hbmOldBuffer = (HBITMAP) SelectObject(hdcBuffer, hbmBuffer);

    HDC hdcMem = CreateCompatibleDC(hdc);
    HBITMAP hbmOld1 = (HBITMAP) SelectObject(hdcMem, hbmBackground);
    BitBlt(hdcBuffer, background.x, background.y, background.width, background.height, hdcMem, 0, 0, SRCCOPY);

    if(gameOverMenuActive)
    {
        hbmBackground = (HBITMAP) LoadImage(NULL, "Resources\\Menus\\GameOver.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
        HBITMAP hbmOld1 = (HBITMAP) SelectObject(hdcMem, hbmBackground);
        BitBlt(hdcBuffer, 200, 150, background.width, background.height, hdcMem, 0, 0, SRCCOPY);
        ShowGameOverScreen();
    }
    SelectObject(hdc, hbmOld1);

    HBITMAP hbmOld=0;

    if(!mainMenuActive)
    {
        SelectObject(hdcMem, boy.hbmMask);
        BitBlt(hdcBuffer, boy.x_pos, boy.y_pos, boy.width, boy.height, hdcMem, boy.x_animation*boy.width, boy.y_animation*boy.height, SRCAND);

        hbmOld = (HBITMAP) SelectObject(hdcMem, boy.hbm);
        BitBlt(hdcBuffer, boy.x_pos, boy.y_pos, boy.width, boy.height, hdcMem, boy.x_animation*boy.width, boy.y_animation*boy.height, SRCPAINT);

        SelectObject(hdcMem, girl.hbmMask);
        BitBlt(hdcBuffer, girl.x_pos, girl.y_pos, girl.width, girl.height, hdcMem, girl.x_animation*girl.width, girl.y_animation*girl.height, SRCAND);

        hbmOld = (HBITMAP) SelectObject(hdcMem, girl.hbm);
        BitBlt(hdcBuffer, girl.x_pos, girl.y_pos, girl.width, girl.height, hdcMem, girl.x_animation*girl.width, girl.y_animation*girl.height, SRCPAINT);

        if(goodBlock.x_pos < 400)
        {
            goodBlock.dx = 1;
        }
        else if(goodBlock.x_pos > 490)
        {
            goodBlock.dx = -1;
        }
        SelectObject(hdcMem, goodBlock.hbmMask);
        BitBlt(hdcBuffer, goodBlock.x_pos+=goodBlock.dx, goodBlock.y_pos, goodBlock.width, goodBlock.height, hdcMem, 0, 0, SRCAND);

        hbmOld = (HBITMAP) SelectObject(hdcMem, goodBlock.hbm);
        BitBlt(hdcBuffer, goodBlock.x_pos+=goodBlock.dx, goodBlock.y_pos, goodBlock.width, goodBlock.height, hdcMem, 0, 0, SRCPAINT);
    }
    BitBlt(hdc, 0,0, rect->right, rect->bottom, hdcBuffer, 0,0, SRCCOPY);

    SelectObject(hdcMem, hbmOld);
    DeleteObject(hdcMem);
    DeleteObject(hbmBuffer);

    SelectObject(hdcBuffer, hbmOldBuffer);
    DeleteObject(hdcBuffer);
    DeleteObject(hbmOldBuffer);
}

void CheckInput(HDC hdc)
{
    if(!KEYDOWN(KEY_A) && !KEYDOWN(KEY_D) && !KEYDOWN(KEY_W))
    {
        if(!boy.isJumping() && boy.state!=dead_right)
        {
            if(boy.lastState==running_right)
                boy.setState(standing_right);
            else
                boy.setState(standing_left);
        }
    }
    else if(KEYDOWN(KEY_A))
    {
        boy.moveLeft(hdc);
    }
    else if(KEYDOWN(KEY_D))
    {
        boy.moveRight(hdc);
    }
    if(KEYDOWN(KEY_W))
    {
        boy.jump(hdc);
    }
    if(KEYDOWN(KEY_S))
    {
        boy.setState(standing_right);
    }


    if(!KEYDOWN(VK_UP) && !KEYDOWN(VK_LEFT) && !KEYDOWN(VK_RIGHT))
    {
        if(!girl.isJumping() && girl.state!=dead_right)
        {
            if(girl.lastState==running_right)
                girl.setState(standing_right);
            else
                girl.setState(standing_left);
        }
    }
    else if(KEYDOWN(VK_LEFT))
    {
        girl.moveLeft(hdc);
    }
    else if(KEYDOWN(VK_RIGHT))
    {
        girl.moveRight(hdc);
    }
    if(KEYDOWN(VK_UP))
    {
        girl.jump(hdc);
    }

    if(KEYDOWN(VK_DOWN))
    {
        girl.setState(standing_right);
    }
}

void Initalize(HWND hwnd)
{
    hbmBackground = (HBITMAP) LoadImage(NULL, "Resources\\Menus\\StartMenu.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    BITMAP bitmap;
    GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
    background.width = bitmap.bmWidth;
    background.height=bitmap.bmHeight;

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
}

void InitializeLevel()
{
    hbmBackground = (HBITMAP) LoadImage(NULL, "Resources\\Levels\\level1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    BITMAP bitmap;
    GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
    background.width = bitmap.bmWidth;
    background.height=bitmap.bmHeight;
}

void ShowGameOverScreen()
{
    playAgainButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\PlayAgainButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
    playAgainButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 360, 257, 275, 70, mainHWND, (HMENU)PLAYAGAINBUTTON, NULL, NULL);
    SendMessageW(playAgainButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)playAgainButtonImage);

    mainMenuButtonImage = (HBITMAP)LoadImageW(NULL, L"Resources\\UI\\Buttons\\MainMenuButton.bmp", IMAGE_BITMAP, 275, 70, LR_LOADFROMFILE);
    mainMenuButton = CreateWindowW(L"BUTTON", NULL, WS_VISIBLE | WS_CHILD | BS_BITMAP, 360, 337, 275, 70, mainHWND, (HMENU)MAINMENUBUTTON, NULL, NULL);
    SendMessageW(mainMenuButton, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM)mainMenuButtonImage);
}

void Update(HWND hwnd)
{
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    Update(&clientRect);

    HDC hdc = GetDC(hwnd);
    boy.update(hdc);
    girl.update(hdc);
    ReleaseDC(hwnd, hdc);
}

void Render(HWND hwnd){
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    HDC hdc = GetDC(hwnd);
    Draw(hdc, &clientRect);
    ReleaseDC(hwnd, hdc);
}

void ResetLevelParameters()
{
    boy.x_pos = 30;
    boy.y_pos = 0;
    girl.x_pos = 5;
    girl.y_pos = 0;
    boy.setState(standing_right);
    girl.setState(standing_right);
}
