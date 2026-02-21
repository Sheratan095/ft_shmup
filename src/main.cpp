#include "ft_shmup.hpp"

void	switchInput(int ch, Game *game);

unsigned long long frame_count = 0;

int main() {
	Screen scr;
	scr.init();
	int marginPlayersLine = 5;

	Game game(1, scr.getHeight() - marginPlayersLine, scr.getWidth(), scr.getHeight()); // Start with 1 player, screen height minus margin, and screen width

	bool running = true;
	while (running)
	{
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

		switchInput(getch(), &game);
	}

	// scr.end() is called automatically by the destructor when scr goes out of scope
	return 0;
}

void	switchInput(int ch, Game *game)
{
	switch (ch)
	{
		case 'a':
		case 'A':
			game->playerMove(0, -1);
			break;

		case 'd':
		case 'D':
			game->playerMove(0, 1);
			break;

		case 'w':
		case 'W':
			game->playerShoot(0);
			break;

		case KEY_LEFT:
			game->playerMove(1, -1);
			break;

		case KEY_RIGHT:
			game->playerMove(1, 1);
			break;

		case KEY_UP:
			game->playerShoot(1);
			break;

		case 'q':
		case 'Q':
			exit(0);
			break;

		default:
			break;
	}
}