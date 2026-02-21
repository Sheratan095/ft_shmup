#include "Screen.hpp"

Screen::Screen() : _width(0), _height(0)
{
}

Screen::~Screen()
{
    end();
}

void Screen::init()
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    // Gobal game timer
    startTime = clock();
    // Enable resize events
    nodelay(stdscr, TRUE);

    getmaxyx(stdscr, _height, _width);
}

clock_t Screen::getCurrentTime()
{
    return clock() - startTime;
}

void Screen::end()
{
    curs_set(1);
    endwin();
}

void Screen::clear()
{
    ::clear();
}

void Screen::refresh()
{
    ::refresh();
}

void Screen::handleResize()
{
    endwin();
    refresh();
    clear();

    getmaxyx(stdscr, _height, _width);
}

int Screen::getWidth() const
{
    return _width;
}
    int     getHeight() const;

int Screen::getHeight() const
{
    return _height;
}