#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "ft_shmup.hpp"

class Game
{
	private:
		list<Player*>	_players; // [0: WASD, 1: ARROWS]
		list<AEnemy*>	_enemies;
		list<Bullet*>	_enemiesBullets;
		list<Bullet*>	_playersBullets;
		list<Asteroid*>	_asteroids;
		int				_score = 0;
		bool			_started = false;
		int				_screenWidth;
		int				_screenHeight;
		int				_playerStartY;

	public:
		Game(int numPlayers, int playerStartY, int screenWidth, int screenHeight);
		~Game();

		void    stop();
		void	start();
		void	update();
		bool	isGameOver() const;
		void    showEntities(Screen& screen) const;
		void	cleanDeathEntities();
		bool    isRunning() const;

		int		getPlayerHealth(int playerId) const;
		int		getScore() const;
		void	setHeight(int newH);
		void	setWidth(int newW);

		void	addMinion();
		void	addBoss();
		void	addAsteroid();

		bool	playerMove(int playerId, int deltaX);
		void	playerShoot(int playerId);

		class InvalidParameters : public std::exception { const char *what() const throw(); };

		class GameNotStarted : public std::exception { const char *what() const throw(); };

};

#endif
