#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <bits/stdc++.h>
#include "player.h"

using namespace std;

#define PRITISNUTO(vk_code) ((GetAsyncKeyState(vk_code) & 0x8000) ? 1 : 0)
#define KEY_A 0x41
#define KEY_D 0x44
#define KEY_S 0x53
#define KEY_W 0x57


void CheckInput(HDC);
void Update(HWND);
void Render(HWND);
void Initalize(void);

void Update(RECT*);
void Draw(HDC, RECT*);

LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

HBITMAP hbmBackground;

Player player;

struct Object{
    int width;
    int height;
    int x;
    int y;
}background;

const int ID_TIMER = 1;

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
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

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Code::Blocks Template Windows App"),       /* Title Text */
           WS_OVERLAPPEDWINDOW, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           1500,                 /* The programs width */
           800,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );

    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    Initalize();

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

        HDC hdc = GetDC(hwnd);
        CheckInput(hdc);
        ReleaseDC(hwnd, hdc);

        Update(hwnd);
        Render(hwnd);

        while(GetTickCount()- vrijeme_pocetak < 20)
        {
            Sleep(5);
        }
    }
    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}

/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        SetTimer(hwnd, ID_TIMER, 20000, NULL);
        break;
    case WM_TIMER:
        if(wParam==ID_TIMER)
        {

        }
        break;
    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER);
        PostQuitMessage (0);
        break;
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

    SelectObject(hdc, hbmOld1);

    HBITMAP hbmOld;

    player.x_animation++;
    if(player.x_animation==5)
    {
        player.y_animation++;
        if(player.y_animation == 6)
        {
            player.y_animation=0;
        }
        player.x_animation=0;
    }
    if(player.x_animation==4 && player.y_animation==5)
    {
        player.x_animation=0;
        player.y_animation=0;
    }

    SelectObject(hdcMem, player.hbmMask);
    BitBlt(hdcBuffer, player.x_pos, player.y_pos, player.width, player.height, hdcMem, player.x_animation*player.width, player.y_animation*player.height, SRCAND);

    hbmOld = (HBITMAP) SelectObject(hdcMem, player.hbm);
    BitBlt(hdcBuffer, player.x_pos, player.y_pos, player.width, player.height, hdcMem, player.x_animation*player.width, player.y_animation*player.height, SRCPAINT);

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
    if(PRITISNUTO(KEY_A))
    {
        cout<<"A"<<endl;
        player.moveLeft(hdc);
    }
    else if(PRITISNUTO(KEY_D))
    {
        cout<<"D"<<endl;
        player.moveRight(hdc);
    }
    else if(PRITISNUTO(KEY_W))
    {
        cout<<"W"<<endl;
        player.y_pos-=player.dy;
    }
    else if(PRITISNUTO(KEY_S))
    {
        cout<<"S"<<endl;
        player.y_pos+=player.dy;
    }
    else if(PRITISNUTO(VK_DOWN))
    {
        cout<<"DOWN"<<endl;
        player.gravityEnabled=!player.gravityEnabled;
        cout<<player.gravityEnabled<<endl;
    }
}



void Initalize(void)
{
    hbmBackground = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\testFloor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    player.hbm = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\walkingBlackSmallRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
    player.hbmMask = (HBITMAP) LoadImage(NULL, "Resources\\Sprites\\walkingWhiteSmallRight.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);

    BITMAP bitmap;
    GetObject(player.hbm, sizeof(BITMAP), &bitmap);

    player.width=bitmap.bmWidth/5;
    player.height=bitmap.bmHeight/6;
    player.x_pos=400;
    player.y_pos=250;
    player.type=red;

    GetObject(hbmBackground, sizeof(BITMAP), &bitmap);
    background.width = bitmap.bmWidth;
    background.height=bitmap.bmHeight;

}

void Update(HWND hwnd)
{
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    Update(&clientRect);

    HDC hdc = GetDC(hwnd);
    player.update(hdc);
    ReleaseDC(hwnd, hdc);
}

void Render(HWND hwnd){
    RECT clientRect;
    GetClientRect(hwnd, &clientRect);
    HDC hdc = GetDC(hwnd);
    Draw(hdc, &clientRect);
    ReleaseDC(hwnd, hdc);
}

