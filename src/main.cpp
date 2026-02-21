#include <ncurses.h>
#include <unistd.h>
#include "../includes/Screen.hpp"

unsigned long long frame_count = 0;

int main() {
    Screen scr;
    scr.init();

    bool running = true;
    while (running) {
        scr.clear();

        // Get current dimensions
        int h = scr.getHeight();
        int w = scr.getWidth();

        // UI Drawing logic
        std::string msg = "Press 'q' to quit | Resize the window to test!" + std::to_string(frame_count++) \
        + " time elapsed: " + std::to_string(scr.getCurrentTime() / CLOCKS_PER_SEC) + "s";
        std::string size_info = "Size: " + std::to_string(w) + "x" + std::to_string(h);

        mvprintw(h / 2, (w - msg.length()) / 2, "%s", msg.c_str());
        mvprintw((h / 2) + 1, (w - size_info.length()) / 2, "%s", size_info.c_str());

        scr.refresh();

        // Input handling
        int ch = getch();
        switch (ch) {
            case 'a':
            case 'A':
            case 37: // Left arrow
                // Handle left movement
                break;
            case 'd':
            case 'D':
            case 39: // Right arrow
                // Handle right movement
                break;
            case 'q':
            case 'Q':
                running = false;
                break;
            case KEY_RESIZE:
                scr.handleResize();
                break;
            default:
                break;
        }
    }

    // scr.end() is called automatically by the destructor when scr goes out of scope
    return 0;
}