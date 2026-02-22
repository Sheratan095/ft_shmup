#include "ft_shmup.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public AEntity
{
	private:
		int	_id; // 0: WASD, 1: ARROWS

	public:
		// Main ctor: specify position, symbol and health
<<<<<<< HEAD
		Player(int x, int y, int width, int height, int id) : AEntity(x, y, width, height, "-(^)-", PLAYER_HEALTH, PLAYER_COLOR_PAIR), _id(id)
		{}
=======
		Player(int x, int y, int width, int height, int id) : AEntity(x, y, width, height, "Player", PLAYER_HEALTH), _id(id)
		{
			if (id == 0)
				_colorPair = PLAYER1_COLOR_PAIR;
			else
				_colorPair = PLAYER2_COLOR_PAIR;
		}
>>>>>>> refs/remotes/origin/main

		~Player()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

<<<<<<< HEAD
		Bullet*	shoot() const { return (new Bullet(_x + _width / 2, _y - 1, "A", PLAYER_BULLET_COLOR_PAIR)); }
=======
		Bullet*	shoot() const { return (new Bullet(_x + _width / 2, _y - 1, PLAYER_BULLET_SYMBOL, _colorPair)); }
>>>>>>> refs/remotes/origin/main
};

#endif