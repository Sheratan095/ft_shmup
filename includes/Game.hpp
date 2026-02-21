#ifndef GAME_MANAGER_HPP
#define GAME_MANAGER_HPP

#include "ft_shmup.hpp"

class Game
{
	private:
		list<Player*>	_players; // [0: WASD, 1: ARROWS]
		list<AEnemy*>	_enemies;
		list<Bullet*>	_bullets;
		list<Asteroid*>	_asteroids;
		int				_score = 0;
		bool			_started = false;
		int				_screenWidth;

	public:
		Game(int numPlayers, int screenWidth, int playerStartY);
		~Game();

		void	start();
		void	update();

		int		getPlayerHealth(int playerId) const;
		int		getScore() const;

		bool	playerMove(int playerId, int deltaX);
		void	playerShoot(int playerId);

		class InvalidParameters : public std::exception { const char *what() const throw(); };

		class GameNotStarted : public std::exception { const char *what() const throw(); };

};

#endif
