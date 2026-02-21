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

    // Gobal game time
    startTime = clock();
    // Enable resize events
    nodelay(stdscr, FALSE);

    getmaxyx(stdscr, _height, _width);
}

void Screen::end()
{
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

int Screen::getHeight() const
{
    return _height;
}