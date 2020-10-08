#pragma once
#include <iostream>
#include <string>
#include <Windows.h>
#include "Vec.h"

template<typename T>
inline void AskInput(_In_ const char* inputtext, T& _Inout_opt_ io) //_Inout_opt_ data in and data out and allows NULL to be passed inside the parameter
{
REDOINPUT:
    std::cout << inputtext << std::endl;
    std::cin >> io;
    if (!std::cin)
    {
        std::cin.clear();
        std::cin.seekg(0, std::cin.beg);//the reason why this will work with getline is because beginning of the stream will be empty, and getline doesn't read empty values it just reads all ascii codes up to a newline. So what happens is cin takes out all characters to the first whitespace, then it sets the stream ptr position at that place, this function moves the stream ptr back to the beginning, but since we have taken all the values out of the beginning then they will be empty valued which getline doesn't read. It's way better to use this method because cin.ignore can take 1000times +- more instructions depending on its parameters
        std::cout << "Invalid input" << std::endl;
        goto REDOINPUT;
    }
    std::cin.seekg(0, std::cin.beg);
}
template<typename T>
inline void AskInput(_In_ const wchar_t* inputtext, T& _Inout_opt_ io) //_Inout_opt_ data in and data out and allows NULL to be passed inside the parameter
{
REDOINPUT:
    std::wcout << inputtext << std::endl;
    std::wcin >> io;
    if (!std::wcin)
    {
        std::wcin.clear();
        std::wcin.seekg(0, std::wcin.beg);
        goto REDOINPUT;
    }
    std::wcin.seekg(0, std::wcin.beg);
}
inline void AskInputS(_In_ const char* inputtext, std::string _Inout_opt_& io)
{
    std::cout << inputtext << std::endl;
    std::getline(std::cin, io);
    std::cin.clear();
    std::cin.seekg(0, std::cin.beg);
}

inline COORD GetCursorPosition() {
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO CSBI;
    GetConsoleScreenBufferInfo(hStd, &CSBI);
    return CSBI.dwCursorPosition;
}
inline void SetCursorPosition(int x, int y) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)x, (SHORT)y });
}
inline void SetCursorPosition(COORD coord) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
inline void SetCursorPosition(iVec2D coord) {
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (SHORT)coord.x, (SHORT)coord.y });
}
inline void ShowConsoleCursor(bool bVis)
{
    HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(hStd, &cursorInfo);
    cursorInfo.bVisible = bVis;
    SetConsoleCursorInfo(hStd, &cursorInfo);
}
inline void Clear(iVec2D SP, iVec2D Ext)
{
    for (int y = SP.y; y <= SP.y + Ext.y; y++)
    {
        SetCursorPosition(SP.x, y);
        for (int x = SP.x; x <= SP.x + Ext.x; x++)
            std::wcout << " ";
    }
}