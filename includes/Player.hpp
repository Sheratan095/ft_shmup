#include "ft_shmup.hpp"

#ifndef PLAYER_HPP
#define PLAYER_HPP

class Player : public AEntity
{
	private:
		int	_id; // 0: WASD, 1: ARROWS

	public:
		// Main ctor: specify position, symbol and health
		Player(int x, int y, int sx, int sy, int id) : AEntity(x, y, sx, sy, PLAYER_SYMBOL, PLAYER_HEALTH, PLAYER_COLOR_PAIR), _id(id)
		{}

		~Player()
		{}

		int		getHealth() const { return _health; }
		void	setHealth(int h) { _health = h; }

		void	takeDamage(int d) { _health -= d; if (_health < 0) _health = 0; }
		bool	isAlive() const { return _health > 0; }

		Bullet*	shoot() const { return (new Bullet(_x , _y - 1, PLAYER_BULLET_COLOR_PAIR)); }
};

#endif