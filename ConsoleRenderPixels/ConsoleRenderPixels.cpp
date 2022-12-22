// ConsoleRenderPixels.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <Windows.h>
#include <iostream>
#include <algorithm>
#define PI 3.14

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE) {
            if (MessageBox(0, L"Are you sure?", L"Exit?", MB_YESNO | MB_ICONQUESTION) == IDYES)
                //Release the windows allocated memory  
                DestroyWindow(hwnd);
        }
        return 0;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}
typedef int (*FunctionMath) (double step);
void DrawFunction(HDC mydc,double min, double max,double step,COLORREF COLOR, FunctionMath function)
{
    int pixel = 0;
    for (double i = min; i < max; i += step)
    {
        SetPixel(mydc, pixel, function(i), COLOR);
        pixel++;
    }
}

int main()
{

    //Get a console handle
    HWND myconsole = GetConsoleWindow();
    //Get a handle to device context
    HDC mydc = GetDC(myconsole);

    //Choose any color
    COLORREF COLOR = RGB(255, 255, 255);
    /* Set the console mode to no-echo, raw input, */
  /* and no window or mouse events.              */
    SetWindowLong(myconsole,GWLP_WNDPROC,(LONG)(WNDPROC)&WndProc);
    //Draw pixels
    DrawFunction(mydc, 0, PI * 4, 0.05, COLOR, [](double i) {
        return (int)(50 + 25 * cos(i));
        });
    DrawFunction(mydc, 3, PI * 6, 0.05, COLOR, [](double i) {
        return (int)(100 + 25 * sin(i));
        });

    DrawFunction(mydc, 0,40, 0.05, COLOR, [](double i) {
        return (int)(pow(i,2));
        });


    ReleaseDC(myconsole, mydc);
    std::cin.get();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
