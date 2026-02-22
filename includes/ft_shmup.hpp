#ifndef FT_SHMUP_HPP
#define FT_SHMUP_HPP

#include <iostream>
#include <string>
#include <ncurses.h>
#include <list>
#include <unistd.h>

using namespace std;

#define PLAYER_SYMBOL 'P'
#define MINION_SYMBOL 'M'
#define BOSS_SYMBOL 'B'
#define ASTEROID_SYMBOL 'A'
#define BULLET_SYMBOL '!'

#define PLAYER_HEALTH 5
#define MINION_HEALTH 2
#define BOSS_HEALTH 3
#define ASTEROID_HEALTH 2

#define PLAYER_DAMAGE 1
#define BOSS_DAMAGE 3
#define MINION_DAMAGE 1
#define ASTEROID_DAMAGE 2

#define POINTS_PER_MINION 100
#define POINTS_PER_BOSS 500

#define INVISIBLE_CURSOR 0
#define GRID_SIZE	4

#include "AEntity.hpp"
#include "Screen.hpp"
#include "Bullet.hpp"
#include "Player.hpp"
#include "AEnemy.hpp"
#include "Asteroid.hpp"
#include "Boss.hpp"
#include "Minion.hpp"
#include "Game.hpp"
#include "Screen.hpp"


// void	init_ncurses(Game *game);
// void	init_matrix(Game *game);
// void	draw_grid(Game *game);
// int     handle_input(Game *game);

#endif