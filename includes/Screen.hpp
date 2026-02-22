#pragma once

#include <ctime>
#include <iostream>
#include <ncurses.h>

class Screen
{
public:
    Screen();
    ~Screen();

    void    init();
    void    end();
    void    clear();
    void    refresh();
    void    handleResize();
    clock_t    getCurrentTime();

    int     getWidth() const;
    int     getHeight() const;
    int     initColors();

private:
    clock_t startTime;
    int     _width;
    int     _height;
};