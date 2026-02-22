#ifndef FT_SHMUP_HPP
#define FT_SHMUP_HPP

#include <iostream>
#include <string>
#include <ncurses.h>
#include <string.h>
#include <list>
#include <unistd.h>

using namespace std;

#define MINION_SYMBOL 'Minion'
#define BOSS_SYMBOL 'Boss'
#define ASTEROID_SYMBOL 'Asteroid'
#define PLAYER_SYMBOL 'P'
#define PLAYER_BULLET_SYMBOL '|'
#define BOSS_BULLET_SYMBOL '*'
#define MINION_BULLET_SYMBOL '+'

#define UHD_COLOR_PAIR 8
#define PLAYER1_COLOR_PAIR 1
#define PLAYER2_COLOR_PAIR 4
#define MINION_COLOR_PAIR 2
#define BOSS_COLOR_PAIR 3
#define ASTEROID_COLOR_PAIR 4
#define BOSS_BULLET_COLOR_PAIR 3
#define MINION_BULLET_COLOR_PAIR 2
#define STAR_COLOR_PAIR 6
#define RESET_PAIR 0

#define PLAYER_HEALTH 5
#define MINION_HEALTH 2
#define BOSS_HEALTH 3

#define ASTEROID_HEALTH 1
#define PROP_HEALTH 1
#define PLAYER_DAMAGE 1
#define BOSS_DAMAGE 3
#define MINION_DAMAGE 1
#define ASTEROID_DAMAGE 2

#define POINTS_PER_MINION 100
#define POINTS_PER_BOSS 500
#define POINTS_PER_ASTEROID 50

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
#include "Star.hpp"
#include "Game.hpp"
#include "Screen.hpp"

int ShowMenu(Screen& scr);

#endif