#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif

#include <tchar.h>
#include <windows.h>
#include <iostream>
#include "gameManager.h"
#include "player.h"
#include "resources.h"

using namespace std;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

TCHAR szClassName[] = _T("CodeBlocksWindowsApp");

GameManager* gameManager = nullptr;

const int ID_TIMER = 1;

int WINAPI WinMain(HINSTANCE hThisInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpszArgument,
    int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    //HWND hwndSecondWindow;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof(WNDCLASSEX);

    wincl.hIcon = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_ICON));
    wincl.hIconSm = LoadIcon (hThisInstance, MAKEINTRESOURCE(IDI_ICON));
    //wincl.hCursor = LoadCursor (hThisInstance, MAKEINTRESOURCE(IDC_CURSOR));
    //
    //wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    //wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

    if (!RegisterClassEx(&wincl))
        return 0;

    hwnd = CreateWindowEx(
        0,                   /* Extended possibilites for variation */
        szClassName,         /* Classname */
        _T("Ice&Fire"),       /* Title Text */
        WS_SYSMENU | WS_CAPTION, /* default window */
        CW_USEDEFAULT,       /* Windows decides the position */
        CW_USEDEFAULT,       /* where the window ends up on the screen */
        1016,                 /* The programs width */
        738,                 /* and height in pixels */
        HWND_DESKTOP,        /* The window is a child-window to desktop */
        NULL,                /* No menu */
        hThisInstance,       /* Program Instance handler */
        NULL                 /* No Window Creation data */
    );

    ShowWindow(hwnd, nCmdShow);

    gameManager = new GameManager(hwnd);

    while (TRUE)
    {
        DWORD vrijeme_pocetak;

        if (PeekMessage(&messages, NULL, 0, 0, PM_REMOVE))
        {
            if (messages.message == WM_QUIT)
            {
                break;
            }
            TranslateMessage(&messages);
            DispatchMessage(&messages);
        }

        vrijeme_pocetak = GetTickCount();

        gameManager->Update();

        while (GetTickCount() - vrijeme_pocetak < 20)
        {
            Sleep(5);
        }
    }
    return messages.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        break;
    case WM_TIMER:
        if (wParam == ID_TIMER)
        {
            gameManager->addTime();
        }
        break;
    case WM_DESTROY:
        KillTimer(hwnd, ID_TIMER);
        PostQuitMessage(0);
        break;
    case WM_COMMAND:
    {
        switch (LOWORD(wParam))
        {
        case PLAYBUTTON:
        {
            gameManager->InitializeLevel();
            gameManager->DestroyMainMenu();
            SetTimer(hwnd, ID_TIMER, 1000, NULL);
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
            KillTimer(hwnd, ID_TIMER);

            gameManager->ResetLevelParameters();
            gameManager->InitializeLevel();
            gameManager->DestroyGameOverMenu();
            SetTimer(hwnd, ID_TIMER, 1000, NULL);
        }
        break;
        case MAINMENUBUTTON:
        {
            std::cout << "MAINMENU button pressed" << std::endl;
            KillTimer(hwnd, ID_TIMER);
            gameManager->ResetLevelParameters();
            gameManager->Initialize();
            gameManager->DestroyGameOverMenu();
        }
        break;
        }
    }
    case MM_MCINOTIFY:
    {
         gameManager->playingSound = false;
         mciSendCommand((MCIDEVICEID)lParam, MCI_CLOSE, 0, 0);
    }
    break;
    default:
        return DefWindowProc(hwnd, message, wParam, lParam);
    }
    return 0;
}
