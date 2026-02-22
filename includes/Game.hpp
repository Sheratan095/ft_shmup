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
		list<Star*>		_props;
		int				_score = 0;
		bool			_started = false;
		int				_screenWidth;
		int				_screenHeight;

	public:
		Game(int numPlayers, int playerStartY, int screenWidth, int screenHeight);
		~Game();

		void    stop();
		void	start();
		void	update();
		void	renderBackground();
		bool	isGameOver() const;
		void    showEntities() const;
		void	cleanDeathEntities();
		bool    isRunning() const;

		int		getPlayerHealth(int playerId) const;
		int		getScore() const;
		int		getEnemyCount() const;

		void	setHeight(int newH);
		void	setWidth(int newW);

		void	addMinion();
		void	addBoss();
		void	addAsteroid();
		void	addStar();

		bool	playerMove(int playerId, int deltaX);
		void	playerShoot(int playerId);

		void	bossBehavior(Boss *enemy);

		class InvalidParameters : public std::exception { const char *what() const throw(); };

		class GameNotStarted : public std::exception { const char *what() const throw(); };

};

#endif
