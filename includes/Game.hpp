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

	public:
		Game(int numPlayers);
		~Game();

		void	start();
		void	update();

		int		getPlayerHealth(int playerId) const;
		int		getScore() const;
		int		getElapsedTime() const;

		void	playerMove(int playerId, int deltaX);
		void	playerShoot(int playerId);

};

#endif
