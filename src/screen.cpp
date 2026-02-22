#include "ft_shmup.hpp"

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
    initColors();

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

void Screen::erase()
{
    ::erase();
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

int Screen::getHeight() const
{
    return _height;
}

int Screen::initColors()
{
    if (!has_colors())
        return -1;

    start_color();

    init_color(COLOR_RED, 1000, 0, 0);
    init_color(COLOR_GREEN, 0, 1000, 0);
    init_color(COLOR_YELLOW, 1000, 1000, 0);
    init_color(COLOR_BLUE, 0, 0, 1000);
    init_color(COLOR_MAGENTA, 1000, 0, 1000);
    init_color(COLOR_CYAN, 0, 1000, 1000);
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6, COLOR_CYAN, COLOR_BLACK);
    init_pair(7, COLOR_WHITE, COLOR_BLACK);
    init_pair(UHD_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);

    return 0;
}