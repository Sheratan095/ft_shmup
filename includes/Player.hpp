#include "ft_shmup.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public AEntity
{
	public:
		// Main ctor: specify position, symbol and health
		Player(int x, int y, int width, int height, int id) : AEntity(x, y, width, height, "-(^)-", PLAYER_HEALTH)
		{
			if (id == 0)
				_colorPair = PLAYER1_COLOR_PAIR;
			else
				_colorPair = PLAYER2_COLOR_PAIR;
		}

		~Player()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		Bullet*	shoot() const { return (new Bullet(_x + _width / 2, _y - 1, "|", _colorPair)); }
};

#endif